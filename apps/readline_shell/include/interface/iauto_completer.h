#ifndef IAUTO_COMPLETER_H
#define IAUTO_COMPLETER_H
#include <vector>
#include <string>
#include "data_model/command_data.h"

class IAutoCompleter
{
public:
    IAutoCompleter() = default ;
    virtual ~IAutoCompleter() = default;
    virtual int RequestForComplete(const CommandData &req, std::vector<std::string> &ouput) = 0;
};
#endif /*IAUTO_COMPLETER_H*/