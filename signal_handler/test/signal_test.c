#include <stdbool.h>
#include <unistd.h>

#include "blogger.h"
#include "signal_handler.h"

int main(void)
{
    blog_init(LEVEL_DEBUG);
    signal_handler_init();
    BLOG(LEVEL_INFO, "Into infinite wait for signal ..., pid %d", getpid());
    do {
        sleep(1);
    } while (true);

    return 0;
}
