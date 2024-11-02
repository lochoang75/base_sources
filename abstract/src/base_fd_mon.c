#include "base_fd_mon.h"
#include "scheduler_epollfd.h"
#include "scheduler_selectfd.h"
#include "scheduler_pollfd.h"
#include "poll.h"

struct scheduler_mon *open_scheduler(const char *name, fd_mon_type_t type)
{
}

int register_handler(struct scheduler_mon *scheduler, struct fd_handler *handler)
{
    scheduler->action->handler_register(scheduler, handler);
}

void close_scheduler(struct scheduler_mon *mon)
{
}