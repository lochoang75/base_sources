
#include "blogger.h"

#include "interface/idrawing.h"
#include "view/drawing_factory.h"
#include "view/drawing_ncurses_impl.h"

IDrawing* DrawingFactory::mInstance = nullptr;

IDrawing * DrawingFactory:: MakeDrawingInstance()
{
    if (mInstance == nullptr)
    {
        BLOG(LOG_INFO, "Allocate new instance for drawing");
        mInstance = new DrawingNcursesImpl();
    }
    BLOG(LOG_INFO, "Return instance at %p", mInstance);

    return mInstance;
}