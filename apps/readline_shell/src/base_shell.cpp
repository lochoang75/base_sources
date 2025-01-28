#include "signal_handler.h"
#include "blogger.h"
#include "application_mon.h"

int main()
{
    blog_init(LOG_INFO);
    signal_handler_init();
    ApplicationMon app_mon;
    app_mon.StartApplication();
    blog_deinit();
    return 0;
}