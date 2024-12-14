#include "selectfd_mon.h"

#include <stdlib.h>
#include <sys/select.h>

#include "linked_list.h"
#include "blogger.h"

struct select_event_handler {
    int fd;
    struct mon_request_info *info;
    struct list_node node;
    char ext_data[0];
};

struct select_fd_mon {
    struct scheduler_action action;
    struct list_node handler_list;
    fd_set read_fds;
    fd_set write_fds;
    fd_set except_fds;
    int max_fd;
    bool is_termiated;
    char ext_data[0];
};

static int start_select(struct select_fd_mon *fdmon)
{
    int ret = select(fdmon->max_fd + 1, &fdmon->read_fds, &fdmon->write_fds, &fdmon->except_fds, NULL);
    if (ret == -1)
    {
        BLOG(LOG_ERR, "Select perform failed");
        return -1;
    }
    struct list_node *item = NULL;
    struct list_node *head = &fdmon->handler_list;
    struct mon_event event;
    struct mon_request_info *info = NULL;
    list_for_each(head, item)
    {
        struct select_event_handler *event_handler = container_of(item, struct select_event_handler, node);
        info = event_handler->info;
        event.fd = event_handler->fd;
        event.file_path = info->file_name;
        event.file_path_len = info->file_name_len;
        event.user_data = info->user_data;
        if (FD_ISSET(event_handler->fd, &fdmon->read_fds))
        {
            info->handler->on_read(fdmon->action.container, &event);
        }

        if (FD_ISSET(event_handler->fd, &fdmon->write_fds))
        {
            info->handler->on_write(fdmon->action.container, &event);
        }

        if (FD_ISSET(event_handler->fd, &fdmon->except_fds))
        {
            info->handler->on_exception(fdmon->action.container, &event);
        }
    }
    return 0;
}

static int handler_register_select_impl(struct scheduler_action *action, struct mon_request_info *info)
{
    int ret = 0;
    struct select_fd_mon *select_mon = (struct select_fd_mon*) action->mon_obj;
    size_t data_size = sizeof(struct select_event_handler) + get_request_info_size(info);
    struct select_event_handler *event_handler = malloc(data_size);
    if (event_handler == NULL)
    {
        BLOG(LOG_EMERG, "Failed to allocate memory, size %d", data_size);
        return -1;
    }

    memset(event_handler, 0, data_size);
    event_handler->info = (struct mon_request_info *)event_handler->ext_data;
    event_handler->fd = -1;
    copy_request_info(event_handler->info, info);
    base_error_t error = list_add_tail(&select_mon->handler_list, &event_handler->node);
    if (error != kSUCCESS)
    {
        BLOG(LOG_ERR, "Failed to register handler (%p), ret %d", error);
        ret = -1;
    }
    return ret;
}

static int handler_unregister_select_impl(struct scheduler_action *action __attribute__((unused)), int fd __attribute__((unused)))
{
    return 0;
}

static int start_scheduler_impl(struct scheduler_action *action)
{
    struct select_fd_mon *select_mon = (struct select_fd_mon *)action->mon_obj;
    struct select_event_handler *event_handler = NULL;
    struct mon_event_handler *mon_handler = NULL;
    struct list_node *item = NULL;
    struct list_node *head = &select_mon->handler_list;
    int fd = -1;
    list_for_each(head, item)
    {
        event_handler = container_of(item, struct select_event_handler, node);
        mon_handler = event_handler->info->handler;
        fd = mon_handler->open(event_handler->info->file_name, event_handler->info->user_data);
        if (fd < 0)
        {
            BLOG(LOG_WARNING, "Failed to open file at path %s", event_handler->info->file_name);
            continue;
        }

        event_handler->fd = fd;
        select_mon->max_fd = (select_mon->max_fd > fd)? select_mon->max_fd : fd;
        if (event_handler->info->open_mode & eMON_OPEN_MODE_READ)
        {
            FD_SET(fd, &select_mon->read_fds);
        }

        if (event_handler->info->open_mode & eMON_OPEN_MODE_WRITE)
        {
            FD_SET(fd, &select_mon->write_fds);
        }

        FD_SET(fd, &select_mon->except_fds);
    }
    select_mon->is_termiated = false;
    return start_select(select_mon);
}

static void close_scheduler_impl(struct scheduler_action *action)
{
    struct select_fd_mon *select_mon = action->mon_obj;
    struct list_node *item = NULL;
    BLOG(LOG_INFO, "Free handler list");
    list_for_each(&select_mon->handler_list, item)
    {
        list_remove(item);
        item = item->prev;
        free(item);
    }
    BLOG(LOG_INFO, "Free fd mon");
    free(select_mon);
}

struct scheduler_action *selectfd_open_mon()
{
    struct select_fd_mon *select_mon = malloc(sizeof(struct select_fd_mon));
    if (select_mon == NULL)
    {
        blog_print(LOG_ERR, "Failed to allocate memory, size %d", sizeof(struct select_fd_mon));
        return NULL;
    }

    memset(select_mon, 0, sizeof(struct select_fd_mon));
    select_mon->action.mon_obj = select_mon;
    select_mon->action.handler_register = handler_register_select_impl;
    select_mon->action.handler_unregister = handler_unregister_select_impl;
    select_mon->action.close_action = close_scheduler_impl;
    select_mon->action.start_scheduler = start_scheduler_impl;
    select_mon->is_termiated = false;
    FD_ZERO(&select_mon->read_fds);
    FD_ZERO(&select_mon->write_fds);
    FD_ZERO(&select_mon->except_fds);
    list_init(&select_mon->handler_list);
    return &select_mon->action;
}
