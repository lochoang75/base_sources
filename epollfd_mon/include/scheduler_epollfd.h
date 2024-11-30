#ifndef SCHEDULER_EPOLLFD_H
#define SCHEDULER_EPOLLFD_H
#include "base_fd_mon.h"

struct scheduler_action *epollfd_open_scheduler();
void epollfd_close_scheduler(struct scheduler_mon *mon);
#endif /*EPOLL_MON_H*/
