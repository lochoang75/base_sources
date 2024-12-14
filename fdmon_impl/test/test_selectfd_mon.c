#include "blogger.h"
#include "signal_handler.h"
#include "abstract_event.h"
#include "abstract_fd_mon.h"
#include "unistd.h"
#include "fcntl.h"

static int open_file_request(const char *file_name, void *user_data __attribute__((unused)))
{
    int fd = open(file_name, O_CREAT | O_RDWR, 0600);
    return fd;
}

static void close_file_request(int fd, void *user_data __attribute__((unused)))
{
    close(fd);
}

static int on_exception_handler(scheduler_mon_t *scheduler __attribute__((unused)), struct mon_event *event __attribute__((unused)))
{
    BLOG(LOG_INFO, "File OP fall into exception");
    return 0;
}

static int on_read_handler(scheduler_mon_t *scheduler __attribute__((unused)), struct mon_event *event __attribute((unused)))
{
    BLOG(LOG_INFO, "File read ready callback");
    usleep(100000);
    return 0;
}

static int on_write_handler(scheduler_mon_t *scheduler __attribute__((unused)), struct mon_event *event __attribute__((unused)))
{
    BLOG(LOG_INFO, "File write ready callback");
    usleep(100000);
    return 0;
}

static int on_termiate_handler(scheduler_mon_t * scheduler __attribute((unused)), struct mon_event *event __attribute((unused)))
{
    BLOG(LOG_INFO, "File op termiated callback");
    return 0;
}

static struct mon_event_handler test_handler = {
    .close = close_file_request,
    .open = open_file_request,
    .on_read = on_read_handler,
    .on_write = on_write_handler,
    .on_exception = on_exception_handler,
    .on_terminate = on_termiate_handler
};

int main()
{
    int ret = 0;
    blog_init(LOG_DEBUG);
    BLOG_ENTER();
    signal_handler_init();
    BLOG(LOG_INFO, "Open sched");
    struct scheduler_mon *mon = open_scheduler("select_fd_sched", eMON_USE_SELECT);
    if (mon == NULL)
    {
        BLOG(LOG_ERR, "Failed to open sched, exit");
        return -1;
    }
    BLOG(LOG_INFO, "Make request_info");
    struct mon_request_info *info = make_request_info("test_selectfd", &test_handler);
    set_request_open_mode(info, eMON_OPEN_MODE_READ);
    BLOG(LOG_INFO, "Regiser handler");
    ret = register_handler(mon, info);
    if (ret > 0)
    {
        BLOG(LOG_ERR, "Failed to register handler");
        return -1;
    }

    BLOG(LOG_INFO, "Start sched");
    start_scheduler(mon);
    BLOG_EXIT();
    return 0;
}