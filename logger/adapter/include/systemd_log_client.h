#ifndef SYSTEMD_LOG_CLIENT_H
#define SYSTEMD_LOG_CLIENT_H
#include <string>
#include  "blogger_adapter.h"

class SystemdLogger: public ILoggerAdapter {
public:
    SystemdLogger() = delete;
    SystemdLogger(int level, const char *app_name);
    ~SystemdLogger();
    void PrintLog(const LoggerData *data) const override;

private:
    int mLogLevel;
    std::string mAppName;
};
#endif /*SYSTEMD_LOG_CLIENT_H*/