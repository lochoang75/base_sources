#include "blogger.h"
#include <stdarg.h>
#include <stdlib.h>

#ifndef LOG_BUFFER_SIZE
#define LOG_BUFFER_SIZE (4096)
#endif

#ifdef USE_STATIC_BUFFER
static char log_buffer[LOG_BUFFER_SIZE];
#else
static char *log_buffer = NULL;
#endif 
#ifndef USE_SYSLOG
static int log_level = LEVEL_INFO;
#endif

const char *s_level_tag[] = {
    [LEVEL_INFO] = "INFO",
    [LEVEL_DEBUG] = "DBG",
    [LEVEL_WARNING] = "WARN",
    [LEVEL_ERR] = "ERR",
    [LEVEL_NOTICE] = "NOTI",
    [LEVEL_EMERG] = "EMER",
    [LEVEL_CRIT] = "CRIT",
    [LEVEL_ALERT] = "ALERT"
};

void blog_init(int level)
{
#ifdef USE_SYSLOG
    openlog(NULL, LOG_CONS | LOG_PID, LOG_USER);
#else
    log_level = level;
#endif

#ifndef USE_STATIC_BUFFER
    log_buffer = malloc(LOG_BUFFER_SIZE);
    if (log_buffer == NULL)
    {
        fprintf(stderr, "Unable to allocate buffer for logger, use static\n");
        static char slog_buffer[LOG_BUFFER_SIZE] = {'\0'};
        log_buffer = slog_buffer;
    }
#endif
}

void blog_print(int level, char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    vsnprintf(log_buffer, LOG_BUFFER_SIZE - 1, fmt, arg);
    va_end(arg);
#ifdef USE_SYSLOG
    syslog(level, "%s", log_buffer);
#else
    if (level <= log_level)
    {
        fprintf(stdout, "%s\n", log_buffer);
    }
#endif
}

const char *blog_get_level_tag(int level)
{
    return s_level_tag[level];
}