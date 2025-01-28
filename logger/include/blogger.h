#ifndef BLOGGER_H
#define BLOGGER_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <string.h>
#include "abstract_config.h"
#ifdef USE_SYSLOG
#include <syslog.h>
#define LEVEL_EMERG     LOG_EMERG
#define LEVEL_ALERT     LOG_ALERT
#define LEVEL_CRIT      LOG_CRIT
#define LEVEL_ERR       LOG_ERR
#define LEVEL_WARNING   LOG_WARNING
#define LEVEL_NOTICE    LOG_NOTICE
#define LEVEL_INFO      LOG_INFO
#define LEVEL_DEBUG     LOG_DEBUG
#else
#define LOG_EMERG     0   /* system is unusable */
#define LOG_ALERT     1   /* action must be taken immediately */
#define LOG_CRIT      2   /* critical conditions */
#define LOG_ERR       3   /* error conditions */
#define LOG_WARNING   4   /* warning conditions */
#define LOG_NOTICE    5   /* normal but significant condition */
#define LOG_INFO      6   /* informational */
#define LOG_DEBUG     7   /* debug-level messages */
#endif
#define LEVEL_TAG(level)   blog_get_level_tag(level)
#define FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_FMT_LF(fmt)  "[%s] %s:%d: " fmt "\n"
#define BLOG_NOLF(level, fmt, ...)  blog_print(level, fmt, ##__VA_ARGS__)
#define BLOG(level, fmt, ...)       blog_print(level, LOG_FMT_LF(fmt), LEVEL_TAG(level), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_INFO(fmt, ...)         blog_print(LOG_INFO, LOG_FMT_LF(fmt), LEVEL_TAG(LOG_INFO), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_DEBUG(fmt, ...)        blog_print(LOG_DEBUG, LOG_FMT_LF(fmt), LEVEL_TAG(LOG_DEBUG), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_WARN(fmt, ...)         blog_print(LOG_WARNING, LOG_FMT_LF(fmt), LEVEL_TAG(LOG_WARNING), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_NOTICE(fmt, ...)       blog_print(LOG_NOTICE, LOG_FMT_LF(fmt), LEVEL_TAG(LOG_NOTICE), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_ERR(fmt, ...)          blog_print(LOG_ERR, LOG_FMT_LF(fmt), LEVEL_TAG(LOG_ERR), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_CRIT(fmt, ...)         blog_print(LOG_CRIT, LOG_FMT_LF(fmt), LEVEL_TAG(LOG_CRIT), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_ALERT(fmt, ...)        blog_print(LOG_ALERT, LOG_FMT_LF(fmt), LEVEL_TAG(LOG_ALERT), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_EMERG(fmt, ...)        blog_print(LOG_EMERG, LOG_FMT_LF(fmt), LEVEL_TAG(LOG_EMERG), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_ENTER()                blog_print(LOG_INFO, LOG_FMT_LF("%s"), LEVEL_TAG(LOG_INFO), FILENAME, __LINE__, "Enter ...")
#define BLOG_EXIT()                 blog_print(LOG_INFO, LOG_FMT_LF("%s"), LEVEL_TAG(LOG_INFO), FILENAME, __LINE__, "Leave ...")

void blog_init(int level);
void blog_print(int level, const char *fmt, ...);
const char* blog_get_level_tag(int level);
void blog_deinit();

#ifdef __cplusplus
}
#endif
#endif /*BLOGGER_H*/
