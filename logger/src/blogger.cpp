#include "blogger.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "blogger_server.h"

#ifdef USE_SYSLOG_LOGGER
#include "syslog_log_client.h"
#endif

#ifdef USE_STDLOG_LOGGER
#include "stdout_log_client.h"
#endif

#ifdef USE_FILE_LOGGER
#include "file_log_client.h"
#endif

#ifdef USE_SYSTEMD_LOGGER
#include "systemd_log_client.h"
#endif

static LoggerServer *gLoggerServer = nullptr;

void blog_init(int level, const char *app_name)
{
    if (gLoggerServer == nullptr)
    {
        gLoggerServer = new LoggerServer();
    }

    if (gLoggerServer == nullptr)
    {
        return;
    }


#ifdef USE_SYSLOG_LOGGER
    {
        ILoggerAdapter *adapter = new SyslogLogger(level, app_name);
        if (adapter != nullptr)
        {
            gLoggerServer->AddLogClient(adapter);
        }
    }
#endif /*USE_SYSLOG_LOGGER*/

#ifdef USE_STDLOG_LOGGER
    {
        ILoggerAdapter *adapter = new StdLogger(level, app_name);
        if (adapter != nullptr)
        {
            gLoggerServer->AddLogClient(adapter);
        }
    }
#endif /*USE_STDLOG_LOGGER */

#ifdef USE_SYSTEMD_LOGGER
    {
        ILoggerAdapter *adapter = new SystemdLogger(level, app_name);
        if (adapter != nullptr)
        {
            gLoggerServer->AddLogClient(adapter);
        }
    }
#endif /*USE_SYSTEMD_LOGGER*/

#ifdef USE_FILE_LOGGER
    {
        ILoggerAdapter *adapter = new FileLogger(level, app_name);
        if (adapter != nullptr)
        {
            gLoggerServer->AddLogClient(adapter);
        }
    }
#endif /*USE_FILE_LOGGER*/
}

void blog_deinit(void)
{
    delete gLoggerServer;
}

void blog_print(int level, const char *fmt, ...)
{
    char log_buffer[LOG_BUFFER_SIZE] = {0};
    va_list arg;
    va_start(arg, fmt);
    vsnprintf(log_buffer, LOG_BUFFER_SIZE, fmt, arg);
    va_end(arg);
    gLoggerServer->SendLogToAllChannel(level, log_buffer, 1);
}

void blog_print_raw(int level, const char *fmt, ...)
{
    char log_buffer[LOG_BUFFER_SIZE] = {0};
    va_list arg;
    va_start(arg, fmt);
    vsnprintf(log_buffer, LOG_BUFFER_SIZE, fmt, arg);
    va_end(arg);
    gLoggerServer->SendLogToAllChannel(level, log_buffer, 0);
}

