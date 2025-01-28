#include "control/auto_completer.h"
#include "blogger.h"

AutoCompleter::AutoCompleter()
{
    mLUT.LoadAutoCompleteLUT();
    mHasValidEntry = false;
}

AutoCompleter:: ~AutoCompleter()
{
}

int AutoCompleter:: RequestForComplete(const CommandData &req, std::vector<std::string> &output)
{
    int ret = 0;
    if (!mHasValidEntry || mActiveEntry.GetCommand() != req.GetCommandName())
    {
        BLOG(LOG_INFO, "Command instance has changed, search for new handler");
        if (mLUT.SearchForCommand(req.GetCommandName(), mActiveEntry))
        {
            mHasValidEntry = true;
        } else
        {
            mHasValidEntry = false;
            ret = -1;
        }
    }

    if (mHasValidEntry)
    {
        ret = mActiveEntry.SearchForCompleted(req, output);
    }
    return ret;
}