#include "epollfd_mon.h"

#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>

#include "linked_list.h"
#include "blogger.h"

#define EPOLL_MAX_EVENTS 1024

struct epoll_event_handler {
    int fd;
    struct epoll_event event;
    struct list_node node;
    struct mon_request_info info[0];
};

struct epoll_fd_mon {
    struct scheduler_action action;
    struct list_node handler_list;
    int epoll_fd;
    struct epoll_event events[EPOLL_MAX_EVENTS];
};

static int start_epoll(struct epoll_fd_mon *mon)
{
    struct epoll_event_handler *epoll_ev_handler = NULL;
    struct mon_event mon_event;
    int ntfs = epoll_wait(mon->epoll_fd, mon->events, EPOLL_MAX_EVENTS, -1);
    if (ntfs == -1)
    {
        BLOG(LOG_ERR, "Error while perform epoll, exit");
        close(mon->epoll_fd);
        return -1;
    }

    for (int i = 0; i < ntfs; i++)
    {
        epoll_ev_handler = (struct epoll_event_handler *)mon->events[i].data.ptr;
        mon_event.fd = epoll_ev_handler->fd;
        mon_event.file_path = epoll_ev_handler->info->file_name;
        mon_event.file_path_len = epoll_ev_handler->info->file_name_len;
        mon_event.user_data = epoll_ev_handler->info->user_data;
        if (mon->events[i].events & EPOLLIN)
        {
            epoll_ev_handler->info->handler->on_read(mon->action.container, &mon_event);
        }

        if (mon->events[i].events & EPOLLOUT)
        {
            epoll_ev_handler->info->handler->on_write(mon->action.container, &mon_event);
        }

        if (mon->events[i].events & EPOLLERR)
        {
            epoll_ev_handler->info->handler->on_exception(mon->action.container, &mon_event);
        }
    }
    return 0;
}

static int handler_register_epoll_impl(struct scheduler_action *action , struct mon_request_info *info)
{
    int ret = -1;
    struct epoll_fd_mon *epoll_mon = (struct epoll_fd_mon*)action->mon_obj;
    if (epoll_mon->epoll_fd <= 0)
    {
        BLOG(LOG_ERR, "Epoll init failed");
        return ret;
    }
    size_t data_size = sizeof(struct epoll_event_handler) + get_request_info_size(info);
    struct epoll_event_handler *event_handler = malloc(data_size);
    if (event_handler == NULL)
    {
        BLOG(LOG_ERR, "allocate memory for event handler size %d failed", data_size);
        return ret;
    }
    memset(event_handler, 0, data_size);
    copy_request_info(event_handler->info, info);
    base_error_t error = list_add_tail(&epoll_mon->handler_list, &event_handler->node);
    if (error != kSUCCESS)
    {
        BLOG(LOG_ERR, "Failed to register handler to list");
        return ret;
    }
    return 0;
}

static int handler_unregister_epoll_impl(struct scheduler_action *action, int fd)
{
    struct epoll_fd_mon *epoll_mon = (struct epoll_fd_mon*)action->mon_obj;
    int ret = epoll_ctl(epoll_mon->epoll_fd, EPOLL_CTL_DEL, fd, NULL);
    if (ret != 0)
    {
        BLOG(LOG_ERR, "Try remove fd (%d) return %d, errno: %s", fd, ret, strerror(errno));
        return ret;
    }

    struct list_node *head = &epoll_mon->handler_list;
    struct list_node *item = NULL;
    struct epoll_event_handler *epoll_ev_handler = NULL;
    list_for_each(head, item)
    {
        epoll_ev_handler = container_of(item, struct epoll_event_handler, node);
        if (epoll_ev_handler->fd == fd)
        {
            list_remove(item);
            item = item->prev;
            BLOG(LOG_INFO, "Handler at fd %d (%p) removed", fd, epoll_ev_handler);
            epoll_ev_handler->info->handler->close(fd, epoll_ev_handler->info->user_data);
            epoll_ev_handler->info->handler->on_terminate(action->container, epoll_ev_handler->info->user_data);
            free(epoll_ev_handler);
            break;
        }
    }
    return 0;
}

static int start_scheduler_impl(struct scheduler_action *action)
{
    struct epoll_fd_mon *epoll_mon = (struct epoll_fd_mon*)action->mon_obj;
    struct list_node *head = &epoll_mon->handler_list;
    struct list_node *item = NULL;
    struct epoll_event_handler *epoll_ev_handler = NULL;
    struct mon_event_handler *mon_ev_handler = NULL;
    int fd = -1;
    int ret = 0;
    list_for_each(head, item)
    {
        epoll_ev_handler = container_of(item, struct epoll_event_handler, node);;
        mon_ev_handler = epoll_ev_handler->info->handler;
        if (epoll_ev_handler->info->fd < 0)
        {
            fd = mon_ev_handler->open(epoll_ev_handler->info->file_name, epoll_ev_handler->info->user_data);
            if (fd < 0)
            {
                BLOG(LOG_WARNING, "Failed to open fd for file %s", epoll_ev_handler->info->file_name);
                continue;
            }
        } else
        {
            fd = epoll_ev_handler->info->fd;
        }
        epoll_ev_handler->fd = fd;
        epoll_ev_handler->event.data.ptr = epoll_ev_handler;
        epoll_ev_handler->event.events = EPOLLERR;
        if (epoll_ev_handler->info->open_mode & eMON_OPEN_MODE_READ)
        {
            epoll_ev_handler->event.events |= EPOLLIN;
        }
        if (epoll_ev_handler->info->open_mode & eMON_OPEN_MODE_WRITE)
        {
            epoll_ev_handler->event.events |= EPOLLOUT;
        }

        ret = epoll_ctl(epoll_mon->epoll_fd, EPOLL_CTL_ADD, fd, &epoll_ev_handler->event);
        if (ret < 0)
        {
            BLOG(LOG_ERR, "Failed to add fd %d to epoll, error %s", fd, strerror(errno));
            close(fd);
            epoll_ev_handler->fd = -1;
        }
    }
    return start_epoll(epoll_mon);
}

static void close_scheduler_impl(struct scheduler_action *action)
{
    struct epoll_fd_mon *epoll_mon = (struct epoll_fd_mon*)action->mon_obj;
    struct list_node *item = NULL;
    struct list_node *iter = NULL;
    BLOG(LOG_INFO, "Free handler list");
    list_for_each(&epoll_mon->handler_list, iter)
    {
        list_remove(iter);
        item = iter;
        iter = iter->prev;
        free(item);
    }
    BLOG(LOG_INFO, "Free fd mon");
    free(epoll_mon);
}

struct scheduler_action *epollfd_open_mon()
{
    struct epoll_fd_mon *epoll_mon = malloc(sizeof(struct epoll_fd_mon));
    if (epoll_mon == NULL)
    {
        BLOG(LOG_ERR, "Failed to allocate memory, size %d", sizeof(struct epoll_fd_mon));
        return NULL;
    }

    memset(epoll_mon, 0, sizeof(struct epoll_fd_mon));
    epoll_mon->epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    if (epoll_mon->epoll_fd < 0)
    {
        BLOG(LOG_ERR, "Failed to open epoll fd");
    }
    epoll_mon->action.mon_obj = epoll_mon;
    epoll_mon->action.handler_register = handler_register_epoll_impl;
    epoll_mon->action.close_action = close_scheduler_impl;
    epoll_mon->action.start_scheduler = start_scheduler_impl;
    epoll_mon->action.handler_unregister = handler_unregister_epoll_impl;
    list_init(&epoll_mon->handler_list);
    return &epoll_mon->action;
}
