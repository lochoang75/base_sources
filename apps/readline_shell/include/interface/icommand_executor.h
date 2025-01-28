#ifndef ICOMMAND_EXECUTOR_H
#define ICOMMAND_EXECUTOR_H
#include "data_model/command_data.h"

class ICommandExecutor{
public:
    ICommandExecutor() = default;
    virtual ~ICommandExecutor() = default;
    virtual int ExecuteCommand(CommandData *command) const = 0;
};
#endif /*ICOMMAND_EXECUTOR_H*/