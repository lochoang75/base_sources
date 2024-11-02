#ifndef SCHEDULER_POLLFD_H
#define SCHEDULER_POLLFD_H
#include "base_fd_mon.h"

struct scheduler_action *pollfd_open_scheduler();
void pollfd_close_scheduler(struct scheduler_mon *mon);
#endif /*SCHEDULLER_POLLFD_H*/