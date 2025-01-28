#ifndef COMMAND_DATA_H
#define COMMAND_DATA_H
#include <vector>
#include <string>

class CommandData
{
public:
    CommandData();
    ~CommandData();
    const std::string &GetCommandName() const;
    const std::vector<std::string> &GetArgumentVector() const;
    int SetCommandName(const std::string &command_name);
    int PushNewArgument(const std::string &argument);

private:
    std::string mCommandName;
    std::vector<std::string> mArgumentList;
};
#endif /*COMMAND_DATA_H*/
