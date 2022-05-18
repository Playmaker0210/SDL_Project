// lop ve hinh bang SDL
#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "GeneralFunc.h"

struct Geometric
{
    Geometric(int left, int top, int width, int height)
    {
        left_=left;
        top_=top;
        width_=width;
        height_=height;
    }
    int left_;
    int top_;
    int width_;
    int height_;
};

struct ColorData
{
    ColorData(Uint8 r, Uint8 g, Uint8 b)
    {
        red_=r;
        green_=g;
        blue_=b;
    }
    Uint8 red_, green_, blue_;
};

class Draw
{
public:
    static void RenderRect(Geometric& rect_size, const ColorData& color_data, SDL_Renderer* screen);
    static void RenderOutline(Geometric& rect_size, const ColorData& color_data, SDL_Renderer* screen);

private:
};

#endif // DRAW_H_INCLUDED
