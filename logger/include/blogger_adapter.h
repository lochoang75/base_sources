#ifndef LOGGER_CLIENT_H
#define LOGGER_CLIENT_H

struct LoggerData
{
    int level;
    const char *msg;
    int endline;
};


class ILoggerAdapter {
public:
    virtual ~ILoggerAdapter() = default;
    virtual void PrintLog(const LoggerData *data) const = 0;
};

namespace log_adapter
{
    const char *log_adapter_get_level_tag(int level);

} // namespace log_adapter

#endif /*LOGGER_CLIENT_H*/