#ifndef BASE_FD_MON_H
#define BASE_FD_MON_H
#include "abstract_enum.h"
#include "abstract_event.h"
struct scheduler_action{
    void *mon_obj;
    scheduler_mon_t *container;
    void (*close_action)(struct scheduler_action *action);
    int (*handler_register)(struct scheduler_action *action, struct mon_request_info *handler);
    int (*handler_unregister)(struct scheduler_action *action, int fd);
    int (*start_scheduler)(struct scheduler_action *action);
};

scheduler_mon_t * open_scheduler(const char *name, mon_type_t type);
int register_handler(scheduler_mon_t *scheduler, struct mon_request_info *handler);
int unregister_handler(scheduler_mon_t *scheduler, int fd);
void close_scheduler(scheduler_mon_t *mon);
int start_scheduler(scheduler_mon_t *mon);
#endif /*BASE_FD_MON_H*/
