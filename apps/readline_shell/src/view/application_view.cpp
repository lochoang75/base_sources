#include "blogger.h"
#include "interface/iauto_completer.h"
#include "view/application_view.h"

ApplicationView:: ApplicationView(IAutoCompleter *completer, IDrawing *drawing): mCompleter(completer), mDrawing(drawing)
{
    //mDrawing->InitWindows(300, 300);
}

ApplicationView:: ~ApplicationView()
{
}

int ApplicationView:: StartUIThread()
{
    CommandData example_command;
    std::vector<std::string> possible_arg;
    example_command.SetCommandName("ex");
    example_command.PushNewArgument("ex_p1");
    if (mCompleter->RequestForComplete(example_command, possible_arg) == 0)
    {
        BLOG_NOLF(LOG_INFO, "Possbile argument:");
        for (auto item = possible_arg.begin(); item != possible_arg.end(); item ++)
        {
            BLOG_NOLF(LOG_INFO, " %s", (*item).c_str());
        }
    }
    //DrawingRequest request{10, 10};
    //request.SetDrawingText("Basic shell implementation");
    //mDrawing->DrawText(request);
    return 0;
}

int ApplicationView:: StopUIThread()
{
    return 0;
}