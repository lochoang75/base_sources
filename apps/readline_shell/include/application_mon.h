#ifndef APPLICATION_MON_H
#define APPLICATION_MON_H
#include "interface/iauto_completer.h"
#include "interface/icommand_executor.h"
#include "interface/idrawing.h"
#include "view/application_view.h"

class ApplicationMon
{
public:
    ApplicationMon();
    ~ApplicationMon();
    void StartApplication();
private:
    IDrawing *mDrawing;
    ICommandExecutor *mExecutor;
    IAutoCompleter *mCompleter;
    ApplicationView *mAppView;
};
#endif /*APPLICATION_MON_H*/