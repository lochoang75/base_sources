#ifndef POSIX_TIMER_H
#define POSIX_TIMER_H
#define TIMER_MINIMUM_INTERVAL_MS       10
#include <time.h>

typedef void (*posix_timer_expire_cb_t)(void *user_data);

int posix_timer_open(time_t interval_ms, posix_timer_expire_cb_t cb,  void *user_data);
void posix_timer_close();
int posix_timer_is_initialized();
#endif /*POSIX_TIMER_H*/