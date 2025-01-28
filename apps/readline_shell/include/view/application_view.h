#ifndef APPLICATION_VIEW_H
#define APPLICATION_VIEW_H
#include "interface/iauto_completer.h"
#include "interface/idrawing.h"

class ApplicationView
{
public:
    ApplicationView() = delete;
    ApplicationView(IAutoCompleter *completer, IDrawing *drawing);
    ~ApplicationView();
    int StartUIThread(void);
    int StopUIThread(void);
private:
    IAutoCompleter *mCompleter;
    IDrawing *mDrawing;
};
#endif /*APPLICATION_VIEW_H*/