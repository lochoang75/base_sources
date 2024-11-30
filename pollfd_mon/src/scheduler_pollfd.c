#include "scheduler_pollfd.h"
#include <stdlib.h>
#include <poll.h>
#include "linked_list.h"

#include "blogger.h"

struct poll_fd_mon {
    struct scheduler_action action;
};

static int handler_register_poll_impl(struct scheduler_mon *mon __attribute__((unused)), struct fd_handler *handler __attribute__((unused)))
{
    return 0;
}

struct scheduler_action *pollfd_open_scheduler()
{
    struct poll_fd_mon *poll_mon = malloc(sizeof(struct poll_fd_mon));
    if (poll_mon == NULL)
    {
        blog_print(LEVEL_ERR, "Failed to allocate memory, size %d", sizeof(struct poll_fd_mon));
        return NULL;
    }

    poll_mon->action.priv_data = poll_mon;
    poll_mon->action.handler_register = handler_register_poll_impl;
    return &poll_mon->action;
}

void pollfd_close_scheduler(struct scheduler_mon *mon __attribute__((unused)))
{
}
