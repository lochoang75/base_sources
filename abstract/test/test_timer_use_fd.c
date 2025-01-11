#include <stdbool.h>

#include "abstract_timer.h"
#include "blogger.h"
#include "abstract_utils.h"
#include "abstract_fd_mon.h"

static bool oneshot_exit = false;
static bool repeate_exit = false;
static time_t oneshot_data = 0;
static struct example_struct {
    time_t set_time;
    int counter;
} repeat_data = {
    .set_time = 0,
    .counter = 5
};

void timer_oneshot_callback(timer_instance_t *timer, void *user_data)
{
    time_t cb_time = time(NULL);
    int *data = (int*) user_data;
    BLOG(LOG_INFO, "Receive call back from instance %p, delta cb time %d", timer, cb_time - (*data));
    timer_close(timer);
    oneshot_exit = true;
}

void timer_repeat_callback(timer_instance_t *timer, void *user_data)
{
    time_t cb_time = time(NULL);
    struct example_struct *data = (struct example_struct*) user_data;
    BLOG(LOG_INFO, "Receive call back from instance %p, delta cb time %d", timer, cb_time - data->set_time);
    data->counter -= 1;
    data->set_time = cb_time;
    if (data->counter == 0)
    {
        timer_close(timer);
        repeate_exit = true;
    }
}

int main(void)
{
    blog_init(LOG_DEBUG);
    scheduler_mon_t *mon = open_scheduler("TimerFdSched", eMON_USE_POLL);
    if (mon == NULL)
    {
        BLOG(LOG_ERR, "Failed to open fd scheduler");
        return -1;
    }

    oneshot_data = time(NULL);
    struct timer_info oneshot_info = {
        .callback = timer_oneshot_callback,
        .expire_ms = 1000,
        .type = eTIMER_ONESHOT,
        .user_data = &oneshot_data
    };

    repeat_data.set_time = time(NULL);
    struct timer_info repeat_info= {
        .callback = timer_repeat_callback,
        .expire_ms = 2000,
        .type = eTIMER_REPEAT,
        .user_data = &repeat_data
    };

    if (timer_fd_open(mon, &oneshot_info) < 0)
    {
        BLOG(LOG_ERR, "Failed to open oneshot timer use fd");
        return -1;
    }
    BLOG(LOG_INFO, "Open oneshot timer success");

    if (timer_fd_open(mon, &repeat_info) < 0)
    {
        BLOG(LOG_ERR, "Failed to open repeat timer use fd");
        return -1;
    }
    BLOG(LOG_INFO, "Open repeat timer success");

    start_scheduler(mon);
    BLOG(LOG_INFO, "Exit...");
    blog_deinit();
    return 0;
}