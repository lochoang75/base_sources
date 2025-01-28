#include "control/auto_complete_entry.h"
#include "blogger.h"

AutoCompleteStaticParam::AutoCompleteStaticParam(std::vector<std::string> param): mPossbileParam(param)
{
}

AutoCompleteStaticParam::~AutoCompleteStaticParam()
{
}


std::vector<std::string> AutoCompleteStaticParam::GetPossibleParameter(const CommandData &req) const
{
    return mPossbileParam;
}

AutoCompleteDynamicParam::AutoCompleteDynamicParam(get_argument_t get_argument)
{
    mDynmaicParam = get_argument;
}

AutoCompleteDynamicParam::~AutoCompleteDynamicParam()
{
}

std::vector<std::string> AutoCompleteDynamicParam::GetPossibleParameter(const CommandData &req) const
{
    std::vector<std::string> possible_arg;
    mDynmaicParam(req, possible_arg);
    return possible_arg;
}

AutoCompleteEntry:: AutoCompleteEntry()
{
}

AutoCompleteEntry::AutoCompleteEntry(const AutoCompleteEntry &other)
{
    this->mParamList = other.mParamList;
    this->mCommand = other.mCommand;
}

AutoCompleteEntry::~AutoCompleteEntry()
{
    for(auto item = mParamList.begin(); item != mParamList.end(); item++)
    {
        delete (*item);
    }
}

void AutoCompleteEntry::SetCommand(const char *command)
{
    mCommand = std::string(command);
}

std::string AutoCompleteEntry::GetCommand() const
{
    return mCommand;
}

void AutoCompleteEntry::AddDynamicParameter(get_argument_t dynamic_param)
{
    IAutoCompleteParam *param = new AutoCompleteDynamicParam(dynamic_param);
    if (param == nullptr)
    {
        BLOG(LOG_ERR, "Failed to allocate memmory for dynamic parameter" );
        return;
    }

    BLOG(LOG_INFO, "Dynamic parameter %p added to position %d", param, mParamList.size());
    mParamList.push_back(param);
    return;
}

void AutoCompleteEntry::AddStaticParameter(std::vector<std::string> parameter)
{
    IAutoCompleteParam *param = new AutoCompleteStaticParam(parameter);
    if (param == nullptr)
    {
        BLOG(LOG_ERR, "Failed to allocate memroy for static parameter");
        return;
    }

    BLOG(LOG_INFO, "Static parameter %p added to position %d", param, mParamList.size());
    mParamList.push_back(param);
    return;
}

int AutoCompleteEntry::SearchForCompleted(const CommandData &req, std::vector<std::string> &output)
{
    int param_index = req.GetArgumentVector().size();
    if (param_index >= mParamList.size())
    {
        BLOG(LOG_NOTICE, "Param index %d over %d, return", param_index, mParamList.size());
        return -1;
    }

    output = mParamList.at(param_index)->GetPossibleParameter(req);
    BLOG(LOG_INFO, "Trigger auto search, return %d possible arg", output.size());
    return 0;
}