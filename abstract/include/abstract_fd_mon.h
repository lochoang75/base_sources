#ifndef BASE_FD_MON_H
#define BASE_FD_MON_H
#include "abstract_enum.h"
#include "abstract_event.h"
struct scheduler_action{
    void *container;
    void *priv_data;
    void (*close_action)(struct scheduler_action *action);
    int (*handler_register)(struct scheduler_action *action, struct fd_handler *handler);
    int (*start_scheduler)(struct scheduler_action *action);
};

struct scheduler_mon {
    char *scheduler_name;
    fd_mon_type_t scheduler_type;
    struct scheduler_action *action;
};

struct scheduler_mon * open_scheduler(const char *name, fd_mon_type_t type);
int register_handler(struct scheduler_mon *scheduler, struct fd_handler *handler);
void close_scheduler(struct scheduler_mon *mon);
int start_scheduler(struct scheduler_mon *mon);
#endif /*BASE_FD_MON_H*/
