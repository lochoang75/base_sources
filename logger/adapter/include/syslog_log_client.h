#ifndef SYSLOG_LOG_CLIENT_H
#define SYSLOG_LOG_CLIENT_H
#include <string>
#include "blogger_adapter.h"

class SyslogLogger: public ILoggerAdapter{
public:
    SyslogLogger() = delete;
    SyslogLogger(int level, const char *app_name);
    ~SyslogLogger();
    void PrintLog(const LoggerData *data) const override;

private:
    int mLevel;
    std::string mAppName;
};
#endif /*SYSLOG_LOG_CLIENT_H*/