#include <stdlib.h>

#include "abstract_fd_mon.h"
#include "abstract_string_helper.h"

#include "blogger.h"
#include "scheduler_epollfd.h"
#include "scheduler_select.h"
#include "scheduler_pollfd.h"

struct scheduler_mon *open_scheduler(const char *name, fd_mon_type_t type)
{
    int data_size = sizeof(struct scheduler_mon) + strlen(name) + 1;
    struct scheduler_mon *mon = malloc(data_size);
    if (mon == NULL)
    {
        BLOG(LOG_ERR, "Failed to allocate memory");
        return NULL;
    }

    memset(mon, 0, data_size);
    memcpy(mon->scheduler_name, name, strlen(name));
    switch (type)
    {
    case FD_MON_USE_EPOLL:
        mon->scheduler_type = FD_MON_USE_EPOLL;
        mon->action = epollfd_open_scheduler();
        break;
    case FD_MON_USE_POLL:
        mon->scheduler_type = FD_MON_USE_POLL;
        mon->action = pollfd_open_scheduler();
        break;
    case FD_MON_USE_SELECT:
        mon->scheduler_type = FD_MON_USE_SELECT;
        mon->action = selectfd_open_scheduler();
        break;
    default:
        BLOG(LOG_ERR, "Unable to open scheduler for type: %s", fd_mon_to_string(type));
        break;
    }

    if (mon->action == NULL)
    {
        free(mon);
        mon = NULL;
    }
    return mon;
}

int register_handler(struct scheduler_mon *scheduler, struct fd_handler *handler)
{
    if (scheduler == NULL || handler == NULL)
    {
        BLOG(LOG_ERR, "invalid scheduler (%p), handler (%p)", scheduler, handler);
        return -1;
    }
    return scheduler->action->handler_register(scheduler->action, handler);
}

void close_scheduler(struct scheduler_mon *scheduler)
{
    if (scheduler == NULL || scheduler->action == NULL)
    {
        return;
    }
    scheduler->action->close_action(scheduler->action);
    free(scheduler);
}

int start_scheduler(struct scheduler_mon *scheduler)
{
    return scheduler->action->start_scheduler(scheduler->action);
}
