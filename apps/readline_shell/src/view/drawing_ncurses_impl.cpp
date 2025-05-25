#include "view/drawing_ncurses_impl.h"

DrawingNcursesImpl:: DrawingNcursesImpl(): mWindows(nullptr), mWindowsWidth(0), mWindowsHeight(0)
{
    //initscr();
    //clear();
    //noecho();
    //cbreak();
    //curs_set(0);
}

int DrawingNcursesImpl::InitWindows(int w, int h)
{
    mWindowsHeight = h;
    mWindowsWidth = w;
    mWindows = newwin(mWindowsHeight, mWindowsWidth, 0, 0);
    keypad(mWindows, TRUE);
    return 0;
}

DrawingNcursesImpl:: ~DrawingNcursesImpl()
{
    if (mWindows != nullptr)
    {
        endwin();
    }
}

int DrawingNcursesImpl:: RefreshWindow()
{
    refresh();
    return 0;
}

int DrawingNcursesImpl:: ClearScreen()
{
    return 0;
}

int DrawingNcursesImpl:: DrawRect(const DrawingRequest &request)
{
    return 0;
}

int DrawingNcursesImpl:: DrawCircle(const DrawingRequest &request)
{
    return 0;
}

int DrawingNcursesImpl:: DrawText(const DrawingRequest &request)
{
    int x = 0, y = 0;
    std::string text_to_print;
    request.GetPosition(x, y);
    request.GetDrawingText(text_to_print);
    mvwprintw(mWindows, y, x, "%s", text_to_print.c_str());
    return 0;
}