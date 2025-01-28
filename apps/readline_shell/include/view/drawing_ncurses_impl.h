#ifndef DRAWING_NCURSES_IMPL_H
#define DRAWING_NCURSES_IMPL_H
#include "interface/idrawing.h"

class DrawingNcursesImpl: public IDrawing
{
public:
    DrawingNcursesImpl();
    ~DrawingNcursesImpl();
    int RefreshWindow() override;
    int ClearScreen() override;
    int DrawRect() override;
    int DrawTriangle() override;
    int DrawCircle() override;
    int DrawText() override;
};
#endif /*DRAWING_NCURSES_IMPL_H*/