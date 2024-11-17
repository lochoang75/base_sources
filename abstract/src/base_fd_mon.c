#include <stdlib.h>
#include "base_fd_mon.h"
#include "scheduler_epollfd.h"
#include "scheduler_select.h"
#include "scheduler_pollfd.h"
#include "poll.h"

struct scheduler_mon *open_scheduler(const char *name __attribute__((unused)), fd_mon_type_t type __attribute__((unused)))
{
    return NULL;
}

int register_handler(struct scheduler_mon *scheduler, struct fd_handler *handler)
{
    scheduler->action->handler_register(scheduler, handler);
    return 0;
}

void close_scheduler(struct scheduler_mon *mon __attribute__((unused)))
{
}