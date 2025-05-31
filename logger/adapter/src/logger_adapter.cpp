#include "blogger_adapter.h"
#include "blogger.h"

const char *s_level_tag[] = {
    "EMER",
    "ALERT"
    "CRIT",
    "ERR",
    "WARN",
    "NOTI",
    "INFO",
    "DBG",
};

const char *log_adapter:: log_adapter_get_level_tag(int level)
{
    if (level > LOG_DEBUG)
    {
        level = LOG_DEBUG;
    }

    return s_level_tag[level];
}