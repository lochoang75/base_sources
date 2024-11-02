#ifndef BASE_FD_MON_H
#define BASE_FD_MON_H
#include "base_enum.h"
#include "base_event.h"
struct scheduler_action{
    void *container;
    void *priv_data;
    int (*handler_register)(scheduler_mon_t * mon, struct fd_handler *handler);
};

struct scheduler_mon {
    char *schduler_name;
    struct scheduler_action *action;
};

struct scheduler_mon * open_scheduler(const char *name, fd_mon_type_t type);
int register_handler(struct scheduler_mon *scheduler, struct fd_handler *handler);
void close_scheduler(struct scheduler_mon *mon);
#endif /*BASE_FD_MON_H*/