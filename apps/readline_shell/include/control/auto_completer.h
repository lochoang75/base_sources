#ifndef AUTO_COMPLETER_H
#define AUTO_COMPLETER_H
#include "interface/iauto_completer.h"
#include "control/auto_complete_director.h"
#include "control/auto_completer_lut.h"
#include "control/auto_complete_entry.h"

class AutoCompleter: public IAutoCompleter
{
public:
    AutoCompleter();
    ~AutoCompleter();
    int RequestForComplete(const CommandData &req, std::vector<std::string> &output) override;
private:
    AutoCompleterLut mLUT;
    AutoCompleteEntry mActiveEntry;
    bool mHasValidEntry;
};
#endif /*AUTO_COMPLTETER_H*/