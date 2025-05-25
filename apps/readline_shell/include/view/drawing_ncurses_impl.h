#ifndef DRAWING_NCURSES_IMPL_H
#define DRAWING_NCURSES_IMPL_H
#include "interface/idrawing.h"
#include <ncurses.h>

class DrawingNcursesImpl: public IDrawing
{
public:
    DrawingNcursesImpl();
    ~DrawingNcursesImpl();
    int InitWindows(int w, int h) override;
    int RefreshWindow() override;
    int ClearScreen() override;
    int DrawRect(const DrawingRequest &request) override;
    int DrawCircle(const DrawingRequest &request) override;
    int DrawText(const DrawingRequest &request) override;
private:
    WINDOW *mWindows;
    int mWindowsWidth;
    int mWindowsHeight;
};
#endif /*DRAWING_NCURSES_IMPL_H*/