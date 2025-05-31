#ifndef BLOGGER_SERVER_H
#define BLOGGER_SERVER_H
#include <vector>
#include "abstract_errors.h"

#include "blogger_adapter.h"

class LoggerServer {
public:
    LoggerServer();
    ~LoggerServer();
    void SendLogToAllChannel(int level, const char *msg, int endl);;
    base_error_t AddLogClient(ILoggerAdapter *client);
    void RemoveLogClient(ILoggerAdapter *client);

private:
    std::vector<ILoggerAdapter *> mClient;
};
#endif /*BLOGGER_SERVER_H*/