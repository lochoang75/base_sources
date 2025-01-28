#include "data_model/command_data.h"

CommandData:: CommandData(): mCommandName("")
{
}

CommandData:: ~CommandData()
{
}

const std::string& CommandData:: GetCommandName() const
{
    return mCommandName;
}

const std::vector<std::string>& CommandData:: GetArgumentVector() const
{
    return mArgumentList;
}

int CommandData::SetCommandName(const std::string &command_name)
{
    mCommandName = command_name;
    return 0;
}

int CommandData::PushNewArgument(const std::string &argument)
{
    mArgumentList.push_back(argument);
    return mArgumentList.size();
}
