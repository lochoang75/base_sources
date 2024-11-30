#include "scheduler_pollfd.h"

#include <stdlib.h>
#include <poll.h>

#include "blogger.h"
#include "linked_list.h"

struct poll_fd_mon {
    struct scheduler_action action;
    struct list_node list_handler;
};

static int handler_register_poll_impl(struct scheduler_action *action, struct fd_handler *handler)
{
    int ret = 0;
    struct poll_fd_mon *poll_mon = (struct poll_fd_mon*)action->priv_data;
    base_error_t error = list_add_tail(&poll_mon->list_handler, handler, sizeof(handler));
    if (error != kSUCCESS)
    {
        BLOG(LOG_ERR, "Unable to add handler, error %d", error);
        ret = -1;
    }
    return ret;
}

static int start_scheduler_impl(struct scheduler_action *action __attribute__((unused)))
{
    return 0;
}

static void close_scheduler_impl(struct scheduler_action *action)
{
    //TODO(elliot): delete list handler first
    free(action->priv_data);
    free(action);
}

struct scheduler_action *pollfd_open_scheduler()
{
    struct poll_fd_mon *poll_mon = malloc(sizeof(struct poll_fd_mon));
    if (poll_mon == NULL)
    {
        blog_print(LOG_ERR, "Failed to allocate memory, size %d", sizeof(struct poll_fd_mon));
        return NULL;
    }

    poll_mon->action.priv_data = poll_mon;
    poll_mon->action.handler_register = handler_register_poll_impl;
    poll_mon->action.close_action = close_scheduler_impl;
    poll_mon->action.start_scheduler = start_scheduler_impl;
    return &poll_mon->action;
}
