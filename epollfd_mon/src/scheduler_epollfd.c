#include "scheduler_epollfd.h"
#include "unistd.h"
#include "blogger.h"

struct epoll_fd_mon {
    struct scheduler_action action;
};

static int handler_register_epoll_impl(struct scheduler_mon *mon, struct fd_handler *handler)
{
}

struct scheduler_action *epollfd_open_scheduler()
{
    struct epoll_fd_mon *epoll_mon = malloc(sizeof(struct epoll_fd_mon));
    if (epoll_mon == NULL)
    {
        blog_print(BLOG_ERR, "Failed to allocate memory, size %d", sizeof(struct epoll_fd_mon));
        return NULL;
    }

    epoll_mon->action.priv_data = epoll_mon;
    epoll_mon->ation.handler_register = handler_register_epoll_impl
    return &epoll_mon->action;
}