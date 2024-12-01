#include "scheduler_epollfd.h"
#include <stdlib.h>

#include "blogger.h"

struct epoll_fd_mon {
    struct scheduler_action action;
};

static int handler_register_epoll_impl(struct scheduler_action *action __attribute__((unused)), struct mon_request_info *info __attribute__((unused)))
{
    return 0;
}

static int start_scheduler_impl(struct scheduler_action *action __attribute__((unused)))
{
    return 0;
}

static void close_scheduler_impl(struct scheduler_action *action)
{
    //TODO(elliot): delete list handler first
    free(action->scheduler_obj);
    free(action);
}

struct scheduler_action *epollfd_open_scheduler()
{
    struct epoll_fd_mon *epoll_mon = malloc(sizeof(struct epoll_fd_mon));
    if (epoll_mon == NULL)
    {
        blog_print(LOG_ERR, "Failed to allocate memory, size %d", sizeof(struct epoll_fd_mon));
        return NULL;
    }

    epoll_mon->action.scheduler_obj = epoll_mon;
    epoll_mon->action.handler_register = handler_register_epoll_impl;
    epoll_mon->action.close_action = close_scheduler_impl;
    epoll_mon->action.start_scheduler = start_scheduler_impl;
    return &epoll_mon->action;
}
