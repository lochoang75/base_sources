#include <stdbool.h>

#include "abstract_timer.h"
#include "blogger.h"
#include "abstract_utils.h"

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

int main(int argc __attribute__((unused)), char **argv)
{
    blog_init(LOG_DEBUG, argv[0]);
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

    int ret = timer_open(&oneshot_info);
    if (ret != 0)
    {
        BLOG(LOG_ERR, "Failed to open posix timer oneshot");
        return -1;
    }
    BLOG(LOG_INFO, "Open oneshot timer successful");

    ret = timer_open(&repeat_info);
    if (ret != 0)
    {
        BLOG(LOG_ERR, "Failed to open posix timer repeat");
        return -1;
    }
    BLOG(LOG_INFO, "Open repeat timer successful");
    do {
        safe_sleep_ms(500);
        if (oneshot_exit && repeate_exit)
        {
            break;
        }
    } while (1);
    BLOG(LOG_INFO, "Exit...");
    blog_deinit();
    return 0;
}