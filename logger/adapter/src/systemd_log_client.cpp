#include "systemd_log_client.h"
#include <systemd/sd-journal.h>
#include <cstdio>
#include <cstring>

SystemdLogger:: SystemdLogger(int level, const char *app_name): mLogLevel(level), mAppName(app_name)
{
}

SystemdLogger:: ~SystemdLogger()
{
}

void SystemdLogger:: PrintLog(const LoggerData *data) const
{
    if (data->level <= mLogLevel)
    {
        sd_journal_send(
            "PRIORITY=%d", data->level,
            "APP_NAME=%s", mAppName.c_str(),
            "MESSAGE=%s", data->msg ? data->msg : "",
            NULL);
    }
}