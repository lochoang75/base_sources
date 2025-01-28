#ifndef DRAWING_FACTORY_H
#define DRAWING_FACTORY_H
#include "interface/idrawing.h"


class DrawingFactory
{
public:
    DrawingFactory() = delete;
    ~DrawingFactory() = delete;
    static IDrawing *MakeDrawingInstance();
private:
    static IDrawing *mInstance;
};
#endif /*DRAWING_FACTORY_H*/