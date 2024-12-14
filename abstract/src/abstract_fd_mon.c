#include <stdlib.h>

#include "abstract_fd_mon.h"
#include "abstract_string_helper.h"

#include "blogger.h"
#include "mon_factory.h"

struct scheduler_mon *open_scheduler(const char *name, mon_type_t type)
{
    BLOG_ENTER();
    int data_size = sizeof(struct scheduler_mon) + strlen(name) + 1;
    struct scheduler_mon *mon = malloc(data_size);
    if (mon == NULL)
    {
        BLOG(LOG_ERR, "Failed to allocate memory");
        return NULL;
    }

    memset(mon, 0, data_size);
    memcpy(mon->scheduler_name, name, strlen(name));
    mon->action = make_fd_mon(type);
    if (mon->action != NULL)
    {
        mon->scheduler_type = type;
        mon->action->container = mon;
    } else
    {
        free(mon);
        mon = NULL;
    }
    return mon;
}

int register_handler(struct scheduler_mon *scheduler, struct mon_request_info *info)
{
    if (scheduler == NULL || info == NULL)
    {
        BLOG(LOG_ERR, "invalid scheduler (%p), handler (%p)", scheduler, info);
        return -1;
    }
    return scheduler->action->handler_register(scheduler->action, info);
}

int unregister_handler(struct scheduler_mon *scheduler, int fd)
{
    BLOG_ENTER();
    if (scheduler == NULL)
    {
        BLOG(LOG_ERR, "invalid scheduler (%p), handler (%d)", scheduler, fd);
        return -1;
    }
    return scheduler->action->handler_unregister(scheduler->action, fd);
}

void close_scheduler(struct scheduler_mon *scheduler)
{
    if (scheduler == NULL || scheduler->action == NULL)
    {
        return;
    }
    scheduler->action->close_action(scheduler->action);
    BLOG(LOG_INFO, "Free scheduler");
    free(scheduler);
}

int start_scheduler(struct scheduler_mon *scheduler)
{
    return scheduler->action->start_scheduler(scheduler->action);
}
