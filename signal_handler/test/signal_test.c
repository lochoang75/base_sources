#include <stdbool.h>
#include <unistd.h>

#include "blogger.h"
#include "signal_handler.h"

int main(int argc __attribute__((unused)), char **argv)
{
    blog_init(LOG_DEBUG, argv[0]);
    signal_handler_init();
    BLOG(LOG_INFO, "Into infinite wait for signal ..., pid %d", getpid());
    do {
        sleep(1);
    } while (true);

    return 0;
}
