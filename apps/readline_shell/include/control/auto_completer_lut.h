#ifndef AUTO_COMPLETER_LUT_H
#define AUTO_COMPLETER_LUT_H
#include "control/auto_complete_director.h"
#include "control/auto_complete_entry.h"

class AutoCompleterLut
{
public:
    AutoCompleterLut();
    ~AutoCompleterLut();
    int LoadAutoCompleteLUT();
    int SearchForCommand(std::string cmd, AutoCompleteEntry &entry) const;
private:
    AutoCompleteDirector mDirector;
    std::vector<AutoCompleteEntry*> mCompleteEntry;
};
#endif /*AUTO_COMPLETER_LUT_H*/