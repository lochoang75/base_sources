#include "blogger_server.h"

LoggerServer:: LoggerServer()
{
}

LoggerServer:: ~LoggerServer()
{
    for (auto client: mClient)
    {
        delete client;
    }

    mClient.clear();
}

void LoggerServer:: SendLogToAllChannel(int level, const char *msg, int endl)
{
    LoggerData data = {.level = level, .msg = msg, .endline = endl};

    for (auto client: mClient)
    {
        client->PrintLog(&data);
    }
}

base_error_t LoggerServer:: AddLogClient(ILoggerAdapter *client)
{
    if (client == nullptr)
    {
        return kINVALID_MEM;
    }

    for (auto eclient: mClient)
    {
        if (eclient == client)
        {
            return kSUCCESS;
        }
    }

    mClient.push_back(client);
    return kSUCCESS;
}

void LoggerServer:: RemoveLogClient(ILoggerAdapter *client)
{
    for (auto it = mClient.begin(); it != mClient.end(); it++)
    {
        if(*it == client)
        {
            mClient.erase(it);
            break;
        }
    }
}