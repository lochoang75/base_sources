#include "scheduler_epollfd.h"
#include <stdlib.h>

#include "blogger.h"

struct epoll_fd_mon {
    struct scheduler_action action;
};

static int handler_register_epoll_impl(struct scheduler_mon *mon __attribute__((unused)), struct fd_handler *handler __attribute__((unused)))
{
    return 0;
}

struct scheduler_action *epollfd_open_scheduler()
{
    struct epoll_fd_mon *epoll_mon = malloc(sizeof(struct epoll_fd_mon));
    if (epoll_mon == NULL)
    {
        blog_print(LEVEL_ERR, "Failed to allocate memory, size %d", sizeof(struct epoll_fd_mon));
        return NULL;
    }

    epoll_mon->action.priv_data = epoll_mon;
    epoll_mon->action.handler_register = handler_register_epoll_impl;
    return &epoll_mon->action;
}

void epollfd_close_scheduler(struct scheduler_mon *mon __attribute__((unused)))
{
}
