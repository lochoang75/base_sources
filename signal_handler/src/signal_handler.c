#include "signal_handler.h"
#include <features.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

static void signal_handler(int sig)
{
    BLOG(LOG_ERR, "Receive signal %d(%s)", sig, strsignal(sig));
    signal(sig, SIG_DFL);
    raise(sig);
}

void signal_handler_init(void)
{
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = &signal_handler;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGABRT, &act, NULL);
    sigaction(SIGFPE, &act, NULL);
    sigaction(SIGILL, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGSEGV, &act, NULL);
    signal(SIGPIPE, SIG_IGN);
}
