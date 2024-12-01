#ifndef BASE_FD_MON_H
#define BASE_FD_MON_H
#include "abstract_enum.h"
#include "abstract_event.h"
struct scheduler_action{
    void *scheduler_obj;
    scheduler_mon_t *container;
    void (*close_action)(struct scheduler_action *action);
    int (*handler_register)(struct scheduler_action *action, struct mon_request_info *handler);
    int (*handler_unregister)(struct scheduler_action *action, struct mon_request_info *handler);
    int (*start_scheduler)(struct scheduler_action *action);
};

struct scheduler_mon {
    char *scheduler_name;
    mon_type_t scheduler_type;
    struct scheduler_action *action;
};

struct scheduler_mon * open_scheduler(const char *name, mon_type_t type);
int register_handler(struct scheduler_mon *scheduler, struct mon_request_info *handler);
int unregsiter_handler(struct scheduler_mon *scheduler, struct mon_request_info *handler);
void close_scheduler(struct scheduler_mon *mon);
int start_scheduler(struct scheduler_mon *mon);
#endif /*BASE_FD_MON_H*/
