#ifndef ABSTRACT_TIMER_H
#define ABSTRACT_TIMER_H
#include <time.h>
#include "abstract_config.h"
#ifdef SUPPORT_TIMER_FD_WITH_POLL
#include "abstract_fd_mon.h"
#endif /*SUPPORT_TIMER_FD_WITH_POLL*/
typedef struct timer_instance timer_instance_t;
typedef void (*async_timer_callback_t)(timer_instance_t *timer, void *user_data);

typedef enum {
    eTIMER_ONESHOT = 0,
    eTIMER_REPEAT
} timer_type_t;

struct timer_info {
    timer_type_t type;
    unsigned long expire_ms;
    async_timer_callback_t callback;
    void *user_data;
};

int timer_open(const struct timer_info *info);
int timer_close(timer_instance_t *timer);
int timer_update_type(timer_instance_t *timer, timer_type_t type);
int timer_update_time(timer_instance_t *timer, unsigned long expire_ms);
timer_type_t timer_get_type(timer_instance_t *timer);
unsigned long timer_get_expire_ms(timer_instance_t *timer);

#ifdef SUPPORT_TIMER_FD_WITH_POLL
int timer_fd_open(struct scheduler_mon *mon, const struct timer_info *info);
#endif /*SUPPORT_TIMER_FD_WITH_POLL*/
#endif /*ABSTRACT_TIMER_H*/