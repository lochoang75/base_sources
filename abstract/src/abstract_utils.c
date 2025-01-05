#include "abstract_utils.h"
#include <errno.h>

void safe_sleep_ms(time_t ms)
{
    safe_sleep_us(ms * 1000);
}

void safe_sleep_secs(time_t secs)
{
    safe_sleep_us(secs * 1000000);
}

void safe_sleep_us(time_t us)
{
    struct timespec ts, rem;
    int ret = 0;
    ts.tv_sec = us / 1000000;
    ts.tv_nsec = (us - (ts.tv_sec * 1000000)) * 1000;
    do {
        ret = nanosleep(&ts, &rem);
        if (ret < 0 && errno == EINTR)
        {
            ts = rem;
        } else
        {
            break;
        }
    } while (1);
}