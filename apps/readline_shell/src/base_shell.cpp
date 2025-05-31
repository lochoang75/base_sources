#include "signal_handler.h"
#include "blogger.h"
#include "application_mon.h"

int main(int argc __attribute__((unused)), char **argv)
{
    blog_init(LOG_INFO, argv[0]);
    signal_handler_init();
    ApplicationMon app_mon;
    app_mon.StartApplication();
    blog_deinit();
    return 0;
}