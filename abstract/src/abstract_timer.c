#include "abstract_timer.h"
#include <stdbool.h>
#include <unistd.h>
#ifdef SUPPORT_TIMER_FD_WITH_POLL
#include "abstract_fd_mon.h"
#include "sys/timerfd.h"
#endif /*SUPPORT_TIMER_FD_WITH_POLL*/
#include "posix_timer.h"
#include "linked_list.h"
#include "blogger.h"

struct timer_instance
{
    struct timer_info info;
    int id;
    bool is_active;
    bool async_cleanup;
    unsigned long local_cnt;
    struct list_node node;
    void *fd_mon;
    int fd;
};

static struct _timer_mon
{
    struct list_node timer_head;
    size_t size;
    unsigned long time_slice_ms;
} timer_mon = {
    .timer_head = INIT_HEAD(&timer_mon.timer_head),
    .size = 0,
    .time_slice_ms = TIMER_MINIMUM_INTERVAL_MS
};

static void _timer_info_clone(struct timer_info *dst, const struct timer_info *src)
{
    dst->callback = src->callback;
    dst->expire_ms = src->expire_ms;
    dst->type = src->type;
    dst->user_data = src->user_data;
}

static void posix_timer_expire_interval_callback(void *user_data)
{
    struct list_node *item = NULL;
    struct _timer_mon *timer_mon = (struct _timer_mon*)user_data;

    list_for_each(&timer_mon->timer_head, item)
    {
        struct timer_instance *timer = container_of(item, struct timer_instance, node);
        if (timer->async_cleanup)
        {
            BLOG(LOG_DEBUG, "async: remove timer %d", timer->id);
            list_remove(item);
            item = item->prev;
            free(timer);
            continue;
        }

        timer->local_cnt += timer_mon->time_slice_ms;
        if (timer->local_cnt >= timer->info.expire_ms)
        {
            timer->local_cnt = 0;
            timer->info.callback(timer, timer->info.user_data);
            if (timer->info.type == eTIMER_ONESHOT)
            {
                timer->async_cleanup = true;
            }
        }
    }
}

int timer_open(const struct timer_info *info)
{
    if (info == NULL)
    {
        BLOG(LOG_ERR, "Info is NULL, return", sizeof(struct timer_instance));
        return -1;
    }

    if (posix_timer_is_initialized() == 0)
    {
        posix_timer_open(timer_mon.time_slice_ms, posix_timer_expire_interval_callback, &timer_mon);
    }

    struct timer_instance *new_timer = malloc((sizeof(struct timer_instance)));
    if (new_timer == NULL)
    {
        BLOG(LOG_ERR, "Failed to allocate memory size %d", sizeof(struct timer_instance));
        return -1;
    }
    _timer_info_clone(&(new_timer->info), info);
    new_timer->fd_mon = NULL;
    new_timer->id = list_get_size(&timer_mon.timer_head);
    list_add_tail(&timer_mon.timer_head, &(new_timer->node));
    return 0;
}

int timer_close(timer_instance_t *timer)
{
    if (timer == NULL)
    {
        BLOG(LOG_ERR, "timer is NULL");
        return -1;
    }

    BLOG(LOG_ERR, "request: remove timer %d", timer->id);
    timer->async_cleanup = true;
    return 0;
}

int timer_update_type(timer_instance_t *timer, timer_type_t type)
{
    if (timer == NULL)
    {
        BLOG(LOG_ERR, "timer is NULL");
        return -1;
    }

    timer->info.type = type;
    return 0;
}

int timer_update_time(timer_instance_t *timer, unsigned long expire_ms)
{
    if (timer == NULL)
    {
        BLOG(LOG_ERR, "timer is NULL");
        return -1;
    }
    timer->info.expire_ms =  expire_ms;
    return 0;
}

timer_type_t timer_get_type(timer_instance_t *timer)
{
    if (timer == NULL)
    {
        BLOG(LOG_ERR, "timer is NULL");
        return -1;
    }
    return timer->info.type;
}

unsigned long timer_get_expire_ms(timer_instance_t *timer)
{
    if (timer == NULL)
    {
        BLOG(LOG_ERR, "timer is NULL");
        return -1;
    }
    return timer->info.expire_ms;
}

#ifdef SUPPORT_TIMER_FD_WITH_POLL
static int _timer_rearm(struct timer_instance * timer, int fd)
{
    struct itimerspec its;
    memset(&its, 0, sizeof(struct itimerspec));
    its.it_value.tv_sec = timer->info.expire_ms / 1000;
    its.it_value.tv_nsec = (timer->info.expire_ms - (its.it_value.tv_sec * 1000)) * 1000000;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;
    if(timerfd_settime(fd, 0, &its, NULL) == -1)
    {
        return -1;
    }
    return 0;
}

static int _timer_fd_open(const char *file_name __attribute__((unused)), void *user_data)
{
    struct timer_instance *timer = (struct timer_instance*)user_data;
    int fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (fd < 0)
    {
        BLOG(LOG_ERR, "Failed to open timer %s", file_name);
    }

    struct itimerspec its;
    memset(&its, 0, sizeof(struct itimerspec));
    its.it_value.tv_sec = timer->info.expire_ms / 1000;
    its.it_value.tv_nsec = (timer->info.expire_ms - (its.it_value.tv_sec * 1000)) * 1000000;
    its.it_interval.tv_sec = its.it_value.tv_sec;
    its.it_interval.tv_nsec = its.it_value.tv_nsec;
    if(timerfd_settime(fd, 0, &its, NULL) == -1)
    {
        BLOG(LOG_ERR, "Failed to settime to timer fd");
        close(fd);
        fd = -1;
    }
    return fd;
}

static void _timer_fd_close(int fd, void *user_data __attribute__((unused)))
{
    close(fd);
}

static int _timer_fd_exception_handle(scheduler_mon_t *mon __attribute__((unused)), struct mon_event *event)
{
    struct timer_instance *timer = (struct timer_instance*)event->user_data;
    timer_close(timer);
    return 0;
}

static int _timer_fd_on_read(scheduler_mon_t *mon, struct mon_event *event)
{
    struct timer_instance *timer = (struct timer_instance*)event->user_data;
    if (timer->async_cleanup)
    {
        unregister_handler(mon, event->fd);
        return 0;
    }
    timer->info.callback(timer, timer->info.user_data);
    if (timer->info.type == eTIMER_ONESHOT)
    {
        timer->async_cleanup = true;
    } else if (_timer_rearm(timer, event->fd) < 0)
    {
        unregister_handler(mon, event->fd);
        return -1;
    }
    return 0;
}

static int _timer_fd_on_terminate(scheduler_mon_t *mon __attribute__((unused)), struct mon_event *event)
{
    BLOG(LOG_INFO, "Timer fd remove, user data %p", event->user_data);
    struct timer_instance *timer = (struct timer_instance*)event->user_data;
    free(timer);
    return 0;
}

static struct mon_event_handler timer_fd_handler = {
    .close = _timer_fd_close,
    .open = _timer_fd_open,
    .on_read = _timer_fd_on_read,
    .on_write = NULL,
    .on_terminate = _timer_fd_on_terminate
};

int timer_fd_open(struct scheduler_mon *mon, const struct timer_info *info)
{
    int ret = -1;
    if (mon == NULL || info == NULL)
    {
        BLOG(LOG_ERR, "Monitor is (%p), info (%p)", mon, info);
        return ret;
    }
    struct timer_instance *timer = malloc(sizeof(struct timer_instance));
    if (timer == NULL)
    {
        BLOG(LOG_ERR, "Unable to allocate mem size %d", sizeof(struct timer_instance));
        return ret;
    }
    _timer_info_clone(&timer->info, info);
    struct mon_request_info *mon_request = make_request_info("timer_fd", &timer_fd_handler);
    if (mon_request == NULL)
    {
        BLOG(LOG_ERR, "Unable to allocate mon request data");
        return ret;
    }
    set_request_open_mode(mon_request, eMON_OPEN_MODE_READ);
    set_request_user_data(mon_request, timer);
    ret = register_handler(mon, mon_request);
    if (ret < 0)
    {
        BLOG(LOG_INFO, "Unable to register handler for timerfd");
        return ret;
    }
    return 0;
}
#endif /*SUPPORT_TIMER_FD_WITH_POLL*/
