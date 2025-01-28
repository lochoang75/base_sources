#ifndef AUTO_COMPLETE_ENTRY_H
#define AUTO_COMPLETE_ENTRY_H
#include <vector>
#include <string>

#include "data_model/command_data.h"

typedef int (*get_argument_t)(const CommandData &req, std::vector<std::string> &output);

class IAutoCompleteParam {
public:
    virtual ~IAutoCompleteParam() {};
    virtual std::vector<std::string> GetPossibleParameter(const CommandData &req) const = 0;
};

class AutoCompleteStaticParam: public IAutoCompleteParam {
public:
    AutoCompleteStaticParam() = delete;
    AutoCompleteStaticParam(std::vector<std::string> param);
    ~AutoCompleteStaticParam();
    virtual std::vector<std::string> GetPossibleParameter(const CommandData &req) const override;
private:
    std::vector<std::string> mPossbileParam;
};

class AutoCompleteDynamicParam: public IAutoCompleteParam {
public:
    AutoCompleteDynamicParam() = delete;
    AutoCompleteDynamicParam(get_argument_t get_argument);
    ~AutoCompleteDynamicParam();
    virtual std::vector<std::string> GetPossibleParameter(const CommandData &req) const override;
private:
    get_argument_t mDynmaicParam;
};

class AutoCompleteEntry
{
public:
    AutoCompleteEntry();
    AutoCompleteEntry(const AutoCompleteEntry &other);
    ~AutoCompleteEntry();
    void SetCommand(const char *cmd);
    std::string GetCommand() const;
    void AddStaticParameter(std::vector<std::string> static_param);
    void AddDynamicParameter(get_argument_t dynamic_param);
    int SearchForCompleted(const CommandData &req, std::vector<std::string> &output);
private:
    std::string mCommand;
    std::vector<IAutoCompleteParam*> mParamList;
};
#endif /*AUTO_COMPLETE_ENTRY_H*/