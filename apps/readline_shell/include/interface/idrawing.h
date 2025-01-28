#ifndef IDRAWING_H
#define IDRAWING_H

class IDrawing {
public:
    IDrawing() = default;
    virtual ~IDrawing() {};
    virtual int RefreshWindow() = 0;
    virtual int ClearScreen() = 0;
    virtual int DrawRect() = 0;
    virtual int DrawTriangle() = 0;
    virtual int DrawCircle()  = 0;
    virtual int DrawText() = 0;
};
#endif /*IDRAWING_H*/