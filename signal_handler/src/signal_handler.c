#include "signal_handler.h"
#include <features.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>

static void print_backtrace()
{
    void *array[10];
    char **backtrace_strings;
    int size = 0, i = 0;
    size = backtrace(array, 10);
    backtrace_strings = backtrace_symbols(array, size);
    if (backtrace_strings != NULL)
    {
        BLOG(LOG_ERR, "Backtrace (%d)", size);
        for (i = 0; i < size; i++)
        {
            BLOG(LOG_ERR, "%s", backtrace_strings[i]);
        }
    }

    free(backtrace_strings);
}

static void signal_handler(int sig)
{
    BLOG(LOG_ERR, "Receive signal %d(%s)", sig, strsignal(sig));
    print_backtrace();
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
