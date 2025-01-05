#include "pollfd_mon.h"

#include <stdlib.h>
#include <poll.h>
#include <stdbool.h>

#include "blogger.h"
#define POLL_DEFAULT_EVENTS     POLLERR | POLLHUP | POLLNVAL
#define POLL_FD_SCALE_SIZE      (100)
#define POLL_FD_DEFAULT_SIZE    (100)

struct pollfd_event_handler {
    int fd;
    struct mon_request_info *info;
    struct list_node node;
    char ext_data[0];
};

struct poll_fd_mon {
    struct scheduler_action action;
    struct list_node handler_list;
    struct pollfd *fds;
    size_t fd_count;
    size_t fd_size;
    bool is_termiated;
    bool is_exception;
    char ext_data[0];
};

static int extend_poll_fd_size(struct pollfd **fds, size_t *iosize)
{
    size_t new_size = *iosize + POLL_FD_SCALE_SIZE;
    struct pollfd *new_fds = malloc(sizeof(struct pollfd) * new_size);
    if (new_fds == NULL)
    {
        BLOG(LOG_ERR, "Failed to allocate new size of poll array");
        return -1;
    }
    memset(new_fds, 0, sizeof(struct pollfd) * new_size);
    memcpy(new_fds, *fds, (*iosize) * sizeof(struct pollfd));
    free(*fds);
    *fds = new_fds;
    *iosize = new_size;
    return 0;
}

static struct mon_request_info *get_mon_info_base_on_fd(struct list_node *head, int fd)
{
    BLOG_ENTER();
    struct pollfd_event_handler *event_handler = NULL;
    struct list_node *item = NULL;
    list_for_each(head, item)
    {
        event_handler = container_of(item, struct pollfd_event_handler, node);
        BLOG(LOG_INFO, "Event handler at (%p)", event_handler);
        if (event_handler->fd == fd)
        {
            return event_handler->info;
        }
    }

    BLOG(LOG_ERR, "Get mon info return NULL, fd (%d)", fd);
    return NULL;
}

LOCK_FUNC static int start_pollfd(struct poll_fd_mon *mon)
{
    int ret = 0;
    struct mon_event event;
    struct mon_request_info *info = NULL;
    ret = poll(mon->fds, mon->fd_count, -1);
    if (ret == -1)
    {
        BLOG(LOG_ERR, "Poll error, exit !!!");
        return ret;
    }

    for (size_t i = 0; i < mon->fd_count; i++)
    {
        if (mon->fds[i].revents == 0)
        {
            continue;
        }
        info = get_mon_info_base_on_fd(&mon->handler_list, mon->fds[i].fd);
        event.fd = mon->fds[i].fd;
        event.file_path = info->file_name;
        event.file_path_len = info->file_name_len;
        event.user_data = info->user_data;
        if (mon->fds[i].revents & POLLIN)
        {
            info->handler->on_read(mon->action.container, &event);
        }

        if (mon->fds[i].revents & POLLOUT)
        {
            info->handler->on_write(mon->action.container, &event);
        }

        if (mon->fds[i].revents & (POLLHUP | POLLERR | POLLNVAL))
        {
            info->handler->on_exception(mon->action.container, &event);
        }
    }
    return ret;
}

static int open_fd_for_registered_file(struct poll_fd_mon *poll_mon)
{
    struct pollfd_event_handler *event_handler= NULL;
    struct mon_event_handler *mon_handler = NULL;
    struct list_node *item;
    struct list_node *head = &poll_mon->handler_list;
    int fd = -1;
    poll_mon->fd_count = 0;
    list_for_each(head, item)
    {
        event_handler = container_of(item, struct pollfd_event_handler, node);
        BLOG(LOG_DEBUG, "Data node at (%p)", event_handler);
        mon_handler = event_handler->info->handler;
        if (event_handler->fd > 0)
        {
            fd = event_handler->fd;
        } else if (event_handler->info->fd > 0)
        {
            event_handler->fd = event_handler->info->fd;
            fd = event_handler->info->fd;
        } else
        {
            fd = mon_handler->open(event_handler->info->file_name, event_handler->info->user_data);
            if (fd < 0)
            {
                BLOG(LOG_WARNING, "Failed to open file at path %s", event_handler->info->file_name);
                continue;
            }

            event_handler->fd = fd;
        }

        poll_mon->fds[poll_mon->fd_count].fd = fd;
        poll_mon->fds[poll_mon->fd_count].events = POLL_DEFAULT_EVENTS;
        if (event_handler->info->open_mode & eMON_OPEN_MODE_READ)
        {
            poll_mon->fds[poll_mon->fd_count].events |= POLLIN;
        }

        if (event_handler->info->open_mode & eMON_OPEN_MODE_WRITE)
        {
            poll_mon->fds[poll_mon->fd_count].events |= POLLOUT;
        }
        poll_mon->fd_count ++;
        if (poll_mon->fd_count == poll_mon->fd_size)
        {
            if(extend_poll_fd_size(&poll_mon->fds, &poll_mon->fd_size))
            {
                BLOG(LOG_ERR, "Failed to extend poll fd size %d", poll_mon->fd_size);
                return -1;
            }
        }
    }
    return 0;
}


static int handler_register_poll_impl(struct scheduler_action *action, struct mon_request_info *info)
{
    int ret = 0;
    struct poll_fd_mon *poll_mon = (struct poll_fd_mon*)action->mon_obj;
    size_t data_size = sizeof(struct pollfd_event_handler) + get_request_info_size(info);
    struct pollfd_event_handler *event_handler = malloc(data_size);
    if (event_handler == NULL)
    {
        BLOG(LOG_ERR, "Failed to allocate memory");
        return -1;
    }

    BLOG(LOG_DEBUG, "New data node at (%p), node (%p)", event_handler, &event_handler->node);
    memset(event_handler, 0, data_size);
    event_handler->info = (struct mon_request_info *)event_handler->ext_data;
    copy_request_info(event_handler->info, info);
    event_handler->fd = -1;
    base_error_t error = list_add_tail(&poll_mon->handler_list, &event_handler->node);
    if (error != kSUCCESS)
    {
        BLOG(LOG_ERR, "Unable to add handler, error %d", error);
        ret = -1;
    }
    return ret;
}

static int handler_unregister_poll_impl(struct scheduler_action *action , int fd)
{
    struct poll_fd_mon *poll_mon = (struct poll_fd_mon *)action->mon_obj;
    struct list_node *iter = NULL;
    list_for_each(&poll_mon->handler_list, iter)
    {
        struct pollfd_event_handler *event_handler = container_of(iter, struct pollfd_event_handler, node);
        if (event_handler->fd == fd)
        {
            struct mon_event event = {
                .fd = fd,
                .file_path = event_handler->info->file_name,
                .file_path_len = event_handler->info->file_name_len,
                .user_data = event_handler->info->user_data
            };
            event_handler->info->handler->on_terminate(action->container, &event);
            list_remove(iter);
            iter = iter->prev;
            free(event_handler);
            break;
        }
    }
    return 0;
}

static int start_scheduler_impl(struct scheduler_action *action)
{
    int ret = 0;
    struct poll_fd_mon *poll_mon = (struct poll_fd_mon*)action->mon_obj;
    poll_mon->is_termiated = false;
    do {
        if (open_fd_for_registered_file(poll_mon) != 0)
        {
            poll_mon->is_exception = true;
            ret = -1;
            break;
        }
        if (start_pollfd(poll_mon) < 0)
        {
            poll_mon->is_exception = true;
            ret = -1;
            break;
        }
    } while (!poll_mon->is_termiated);
    return ret;
}

static void close_scheduler_impl(struct scheduler_action *action)
{
    struct poll_fd_mon *pollfd_mon = action->mon_obj;
    struct list_node *iter = NULL;
    BLOG(LOG_INFO, "Free handler list");
    list_for_each(&pollfd_mon->handler_list, iter)
    {
        struct pollfd_event_handler *event_handler = container_of(iter, struct pollfd_event_handler, node);
        list_remove(iter);
        iter = iter->prev;
        free(event_handler);
    }
    BLOG(LOG_INFO, "Free fd mon");
    free(pollfd_mon);
}

struct scheduler_action *pollfd_open_mon()
{
    BLOG_ENTER();
    struct poll_fd_mon *poll_mon = malloc(sizeof(struct poll_fd_mon));
    struct pollfd *fds = malloc(sizeof(struct pollfd) * POLL_FD_DEFAULT_SIZE);
    if (poll_mon == NULL || fds == NULL)
    {
        blog_print(LOG_ERR, "Failed to allocate memory, size %d, %d", sizeof(struct poll_fd_mon), sizeof(struct pollfd) * POLL_FD_DEFAULT_SIZE);
        return NULL;
    }

    memset(fds, 0, sizeof(struct pollfd) * POLL_FD_DEFAULT_SIZE);
    memset(poll_mon, 0, sizeof(struct poll_fd_mon));
    poll_mon->action.mon_obj = poll_mon;
    poll_mon->action.handler_register = handler_register_poll_impl;
    poll_mon->action.handler_unregister = handler_unregister_poll_impl;
    poll_mon->action.close_action = close_scheduler_impl;
    poll_mon->action.start_scheduler = start_scheduler_impl;
    poll_mon->fd_size = POLL_FD_DEFAULT_SIZE;
    poll_mon->fd_count = 0;
    poll_mon->fds = fds;
    poll_mon->is_termiated = true;
    list_init(&poll_mon->handler_list);
    return &poll_mon->action;
}
