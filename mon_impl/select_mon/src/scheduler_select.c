#include "scheduler_select.h"

#include <stdlib.h>

#include "blogger.h"
#include"linked_list.h"

struct select_fd_mon {
    struct scheduler_action action;
};

static int handler_register_select_impl(struct scheduler_action *action __attribute__((unused)), struct mon_request_info *info __attribute__((unused)))
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

struct scheduler_action *selectfd_open_scheduler()
{
    struct select_fd_mon *poll_mon = malloc(sizeof(struct select_fd_mon));
    if (poll_mon == NULL)
    {
        blog_print(LOG_ERR, "Failed to allocate memory, size %d", sizeof(struct select_fd_mon));
        return NULL;
    }

    poll_mon->action.scheduler_obj = poll_mon;
    poll_mon->action.handler_register = handler_register_select_impl;
    poll_mon->action.close_action = close_scheduler_impl;
    poll_mon->action.start_scheduler = start_scheduler_impl;
    return &poll_mon->action;
}
