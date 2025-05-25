#include "interface/idrawing.h"

DrawingRequest::DrawingRequest(): mPosX(0), mPosY(0), mWidth(0),
                                    mHeight(0), mBorderRad(0), mCircleRadius(0),
                                    mDrawingText(""), mFontSize(0)
{
}

DrawingRequest::~DrawingRequest()
{
}

void DrawingRequest::SetPosition(const int &x, const int &y)
{
    mPosX = x;
    mPosY = y;
}

void DrawingRequest::GetPosition(int &x, int &y) const
{
    x = mPosX;
    y = mPosY;
}

void DrawingRequest::SetBoxSize(const int &w, const int &h)
{
    mWidth = w;
    mHeight = h;
}

void DrawingRequest::GetBoxSize(int &w, int &h) const
{
    w = mWidth;
    h = mHeight;
}

void DrawingRequest::SetCircleRadius(const int &rad)
{
    mCircleRadius = rad;
}

int DrawingRequest::GetCircleRadius() const
{
    return mCircleRadius;
}

void DrawingRequest::SetBorderRadius(const int &rad)
{
    mBorderRad = rad;
}

int DrawingRequest::GetBorderRadius() const
{
    return mBorderRad;
}

void DrawingRequest::SetDrawingText(const std::string &text_to_draw)
{
    mDrawingText = text_to_draw;
}

void DrawingRequest::GetDrawingText(std::string &text_to_draw) const
{
    text_to_draw = mDrawingText;
}

void DrawingRequest::SetFontSize(const int &font_size)
{
    mFontSize = font_size;
}

int DrawingRequest::GetFontSize() const
{
    return mFontSize;
}