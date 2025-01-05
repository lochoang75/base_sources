#include "abstract_timer.h"
#include "blogger.h"
#include "abstract_utils.h"

void timer_callback(timer_instance_t *timer, void *user_data)
{
    int *data = (int*) user_data;
    BLOG(LOG_INFO, "Receive call back from instance %p, user data %d", timer, *data);
    timer_close(timer);
}

int main()
{
    blog_init(LOG_DEBUG);
    static int priv_data = 5;
    struct timer_info info = {
        .callback = timer_callback,
        .expire_ms = 100,
        .type = eTIMER_ONESHOT,
        .user_data = &priv_data
    };

    int ret = timer_open(&info);
    if (ret != 0)
    {
        BLOG(LOG_ERR, "Failed to open posix timer");
        return -1;
    }
    safe_sleep_secs(1);
    BLOG(LOG_INFO, "Exit...");
    blog_deinit();
    return 0;
}