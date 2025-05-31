#include <errno.h>
#include "abstract_config.h"
#include "file_log_client.h"

#include "unistd.h"
#define DEFAULT_LOG_FOLDER      "/tmp/"
#define DEFAULT_LOG_FILENAME    "base_log.txt"

FileLogger:: FileLogger(int level, const char *app_name):  mFileName(DEFAULT_LOG_FOLDER DEFAULT_LOG_FILENAME),
                                                        mAppName(app_name),
                                                        mLogLevel(level),
                                                        mFileFp(nullptr)
{
    FILE *fp = fopen(mFileName.c_str(), "w");
    if (fp != nullptr)
    {
        mFileFp = fp;
    }
}

FileLogger:: ~FileLogger()
{
    if (mFileFp)
    {
        fclose(mFileFp);
        mFileFp = nullptr;
    }
}

void FileLogger::PrintLog(const LoggerData *data) const
{
    if (mFileFp == nullptr)
    {
        return;
    }

    if (data->level <= mLogLevel)
    {
        char log_buffer[LOG_BUFFER_SIZE + 10] = {0};
        const char *log_tag = log_adapter::log_adapter_get_level_tag(data->level);
        int num_write = snprintf(log_buffer, LOG_BUFFER_SIZE, "[%s] %s", log_tag, data->msg);
        fwrite(log_buffer, 1, num_write, mFileFp);
        sync();
    }
}