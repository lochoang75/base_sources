#ifndef FILE_LOG_CLIENT_H
#define FILE_LOG_CLIENT_H
#include <string>
#include <fcntl.h>
#include "blogger_adapter.h"

class FileLogger: public ILoggerAdapter {
public:
    FileLogger() = delete;
    FileLogger(int level, const char *app_name);
    ~FileLogger();
    void PrintLog(const LoggerData *data) const override;

private:
    std::string mFileName;
    std::string mAppName;
    int mLogLevel;
    FILE *mFileFp;
};
#endif /*FILE_LOG_CLIENT_H*/