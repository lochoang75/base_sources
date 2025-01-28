#include "control/auto_completer_lut.h"
#include "blogger.h"

AutoCompleterLut::AutoCompleterLut()
{
}

AutoCompleterLut::~AutoCompleterLut()
{
}

int AutoCompleterLut::LoadAutoCompleteLUT()
{
    //TODO(Elliot): Enhance this structure
    mCompleteEntry.push_back(mDirector.MakeExampleCommand());
    return 0;
}

int AutoCompleterLut::SearchForCommand(std::string command, AutoCompleteEntry &entry) const
{
    for (auto item = mCompleteEntry.begin(); item != mCompleteEntry.end(); item++)
    {
        if (command == (*item)->GetCommand())
        {
            entry = *(*item);
            return 1;
        }
    }
    return 0;
}