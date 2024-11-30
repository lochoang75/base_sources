#ifndef BLOGGER_H
#define BLOGGER_H
#include <stdio.h>
#include <string.h>
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
#define LEVEL_EMERG     0   /* system is unusable */
#define LEVEL_ALERT     1   /* action must be taken immediately */
#define LEVEL_CRIT      2   /* critical conditions */
#define LEVEL_ERR       3   /* error conditions */
#define LEVEL_WARNING   4   /* warning conditions */
#define LEVEL_NOTICE    5   /* normal but significant condition */
#define LEVEL_INFO      6   /* informational */
#define LEVEL_DEBUG     7   /* debug-level messages */
#endif
#define LEVEL_TAG(level)   blog_get_level_tag(level)
#define FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_FMT_LF(fmt)  "[%s] %s:%d: "fmt
#define LOG_FMT_NLF(fmt)  "[%s] %s:%d: "fmt"\n"
#define BLOG_NOLF(level, fmt, ...)  blog_print(level, LOG_FMT_NLF(fmt), LEVEL_TAG(level), FILENAME, __LINE__ ##__VA_ARGS__)
#define BLOG(level, fmt, ...)       blog_print(level, LOG_FMT_LF(fmt), LEVEL_TAG(level), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_INFO(fmt, ...)         blog_print(LEVEL_INFO, LOG_FMT_LF(fmt), LEVEL_TAG(LEVEL_INFO), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_DEBUG(fmt, ...)        blog_print(LEVEL_DEBUG, LOG_FMT_LF(fmt), LEVEL_TAG(LEVEL_DEBUG), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_WARN(fmt, ...)         blog_print(LEVEL_WARNING, LOG_FMT_LF(fmt), LEVEL_TAG(LEVEL_WARNING), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_NOTICE(fmt, ...)       blog_print(LEVEL_NOTICE, LOG_FMT_LF(fmt), LEVEL_TAG(LEVEL_NOTICE), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_ERR(fmt, ...)          blog_print(LEVEL_ERR, LOG_FMT_LF(fmt), LEVEL_TAG(LEVEL_ERR), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_CRIT(fmt, ...)         blog_print(LEVEL_CRIT, LOG_FMT_LF(fmt), LEVEL_TAG(LEVEL_CRIT), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_ALERT(fmt, ...)        blog_print(LEVEL_ALERT, LOG_FMT_LF(fmt), LEVEL_TAG(LEVEL_ALERT), FILENAME, __LINE__, ##__VA_ARGS__)
#define BLOG_EMERG(fmt, ...)        blog_print(LEVEL_EMERG, LOG_FMT_LF(fmt), LEVEL_TAG(LEVEL_EMERG), FILENAME, __LINE__, ##__VA_ARGS__)

void blog_init(int level);
void blog_print(int level, char *fmt, ...);
const char* blog_get_level_tag(int level);

#endif /*BLOGGER_H*/
