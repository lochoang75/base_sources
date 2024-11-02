#ifndef SCHEDULER_EPOLLFD_H
#define SCHEDULER_EPOLLFD_H
#include "base_enum.h"
#include "base_fd_mon.h"

struct scheduler_action_iface *epollfd_open_scheduler(const char *name, fd_mon_type_t type);
#endif /*EPOLL_MON_H*/