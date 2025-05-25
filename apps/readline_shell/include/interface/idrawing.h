#ifndef IDRAWING_H
#define IDRAWING_H
#include <string>

class DrawingRequest
{
public:
    DrawingRequest();
    DrawingRequest(const int &x, const int &y): mPosX(x), mPosY(y) {};
    ~DrawingRequest();
    void SetPosition(const int &x, const int &y);
    void GetPosition(int &x, int &y) const;
    void SetBoxSize(const int &w, const int &h);
    void GetBoxSize(int &w, int &height) const;
    void SetCircleRadius(const int &rad);
    int GetCircleRadius() const;
    void SetBorderRadius(const int &rad);
    int GetBorderRadius() const;
    void SetDrawingText(const std::string &text);
    void GetDrawingText(std::string &text) const;
    void SetFontSize(const int &font_size);
    int GetFontSize() const;

private:
    int mPosX;
    int mPosY;
    int mWidth;
    int mHeight;
    int mBorderRad;
    int mCircleRadius;
    std::string mDrawingText;
    int mFontSize;
};

class IDrawing
{
public:
    IDrawing() = default;
    virtual ~IDrawing() {};
    virtual int InitWindows(int w, int h) = 0;
    virtual int RefreshWindow() = 0;
    virtual int ClearScreen() = 0;
    virtual int DrawRect(const DrawingRequest &request) = 0;
    virtual int DrawCircle(const DrawingRequest &request)  = 0;
    virtual int DrawText(const DrawingRequest &request) = 0;
};
#endif /*IDRAWING_H*/