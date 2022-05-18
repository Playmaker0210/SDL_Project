#include "Draw.h"

void Draw::RenderRect(Geometric& rect_size, const ColorData& color_data, SDL_Renderer* screen)
{
    SDL_Rect fill_rect= {rect_size.left_, rect_size.top_, rect_size.width_, rect_size.height_};
    SDL_SetRenderDrawColor(screen, color_data.red_, color_data.blue_, color_data.green_, 255);
    SDL_RenderFillRect(screen, &fill_rect);
}

void Draw::RenderOutline(Geometric& rect_size, const ColorData& color_data, SDL_Renderer* screen)
{
    SDL_Rect out_rect= {rect_size.left_, rect_size.top_, rect_size.width_, rect_size.height_};
    SDL_SetRenderDrawColor(screen, color_data.red_, color_data.green_, color_data.blue_, 255);
    SDL_RenderDrawRect(screen, &out_rect);
}
