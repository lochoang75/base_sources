#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H
#include "interface/icommand_executor.h"
#include "data_model/command_data.h"

class CommandExecutor: public ICommandExecutor
{
public:
    CommandExecutor();
    ~CommandExecutor();
    int ExecuteCommand(CommandData *command) const override;
};
#endif /*COMMAND_EXECUTOR_H*/