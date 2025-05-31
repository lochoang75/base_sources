#include "stdout_log_client.h"
#include <stdio.h>

StdLogger:: StdLogger(int level, const char *app_name): mLogLevel(level), mAppName(app_name)
{
}

StdLogger:: ~StdLogger()
{
}


void StdLogger:: PrintLog(const LoggerData* data) const
{
    if (data->level <= mLogLevel)
    {
        const char *log_tag = log_adapter::log_adapter_get_level_tag(data->level);
        if (data->endline)
        {
            printf("[%s] %s", log_tag, data->msg);
        } else
        {
            printf("[%s] %s\n", log_tag, data->msg);
        }
    }
}