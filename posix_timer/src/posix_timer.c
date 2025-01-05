#include "posix_timer.h"
#include <time.h>
#include <signal.h>
#include <stdbool.h>

#include "blogger.h"

struct posix_timer_data
{
    void *user_data;
    timer_t timer_id;
    int is_initialized;
    posix_timer_expire_cb_t expire_cb;
};

static struct posix_timer_data data = {
    .timer_id = NULL,
    .user_data = NULL,
    .is_initialized = false,
    .expire_cb = NULL
};

static void _posix_timer_callback_handler(int signum __attribute__((unused)))
{
    data.expire_cb(data.user_data);
    return;
}

int posix_timer_open(time_t interval_ms, posix_timer_expire_cb_t cb,  void *user_data)
{
    if (data.is_initialized)
    {
        return -1;
    }

    struct sigaction sa;
    struct sigevent sev;
    struct itimerspec its;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = _posix_timer_callback_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    if (timer_create(CLOCK_MONOTONIC, &sev, &data.timer_id) == -1) {
        BLOG(LOG_ERR, "Failed to create timer");
        return -1;
    }

    its.it_value.tv_sec = interval_ms / 1000;
    its.it_value.tv_nsec = (interval_ms - (its.it_value.tv_sec * 1000)) * 1000000;
    its.it_interval.tv_sec = its.it_interval.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;
    if (timer_settime(data.timer_id, 0, &its, NULL) == -1)
    {
        BLOG(LOG_ERR, "Failed to set time using tier_settime");
        return -1;
    }
    data.expire_cb = cb;
    data.user_data = user_data;
    data.is_initialized = true;
    return 0;
}

void posix_timer_close()
{
    if (data.is_initialized)
    {
        struct sigaction sa;
        sa.sa_flags = SA_SIGINFO;
        sa.sa_handler = SIG_DFL;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGRTMIN, &sa, NULL);

        timer_delete(data.timer_id);
        data.is_initialized = false;
    }
}

int posix_timer_is_initialized()
{
    return (int)data.is_initialized;
}