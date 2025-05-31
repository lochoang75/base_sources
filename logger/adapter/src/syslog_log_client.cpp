#include "syslog_log_client.h"
#include <syslog.h>

SyslogLogger:: SyslogLogger(int level, const char *app_name): mLevel(level), mAppName(app_name)
{
    openlog(app_name, LOG_CONS | LOG_PID, LOG_USER);
}

SyslogLogger:: ~SyslogLogger()
{
    closelog();
}

void SyslogLogger:: PrintLog(const LoggerData *data) const
{
    if (data->level <= mLevel)
    {
        const char *log_tag = log_adapter::log_adapter_get_level_tag(data->level);
        syslog(data->level, "[%s] %s", log_tag, data->msg);
    }
}
