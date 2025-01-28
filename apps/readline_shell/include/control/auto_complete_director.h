#ifndef AUTO_COMPLETER_DIRECTOR_H
#define AUTO_COMPLETER_DIRECTOR_H
#include "control/auto_complete_entry.h"

class AutoCompleteDirector
{
public:
    AutoCompleteDirector();
    ~AutoCompleteDirector();
    AutoCompleteEntry *MakeExampleCommand();
private:
};
#endif /*AUTO_COMPLETER_DIRECTOR_H*/