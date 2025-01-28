#include "application_mon.h"
#include "view/application_view.h"
#include "control/auto_completer.h"
#include "control/command_executor.h"
#include "view/drawing_factory.h"
#include "blogger.h"

ApplicationMon::ApplicationMon(): mDrawing(nullptr), mExecutor(nullptr), mCompleter(nullptr)
{
    mDrawing = DrawingFactory::MakeDrawingInstance();
    mExecutor = new CommandExecutor();
    mCompleter = new AutoCompleter();
    mAppView = new ApplicationView(mCompleter, mDrawing);
    BLOG(LOG_INFO, "Drawing: %p, Executor: %p, Completer: %p, UI: %p",
                    mDrawing, mExecutor, mCompleter, mAppView);
}

ApplicationMon::~ApplicationMon()
{
    delete mExecutor;
    delete mCompleter;
    delete mDrawing;
    delete mAppView;
    mExecutor = nullptr;
    mCompleter = nullptr;
    mDrawing = nullptr;
    mAppView = nullptr;
}

void ApplicationMon:: StartApplication()
{
    BLOG(LOG_INFO, "App Start");
    mAppView->StartUIThread();
}