#ifndef STDOUT_LOGGER_H
#define STDOUT_LOGGER_H
#include <string>
#include "blogger_adapter.h"

class StdLogger: public ILoggerAdapter {
public:
    StdLogger() = delete;
    StdLogger(int level, const char *app_name);
    ~StdLogger();
    void PrintLog(const LoggerData* data) const override;
private:
    int mLogLevel;
    std::string mAppName;
};
#endif /*STDOUT_LOGGER_H*/