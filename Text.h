// lop quan li Text
#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "GeneralFunc.h"
#include "BaseObj.h"

class Text: public baseObject
{
public:
    Text();
    ~Text();

    enum TextColor
    {
        RED_TEXT=0,
        WHITE_TEXT=1,
        BLACK_TEXT=2,
    };

    bool CreateText(SDL_Renderer* screen, TTF_Font* font);
    bool Load_render_text(TTF_Font* font, SDL_Renderer* screen);
    void Reset();
    void Set_color(Uint8 red, Uint8 green, Uint8 blue);
    void Set_color(int type);
    void Render_Text(SDL_Renderer* screen, int xPos, int yPos,
                     SDL_Rect* clip=NULL, double angle = 0.0,
                     SDL_Point* center = NULL,
                     SDL_RendererFlip flip= SDL_FLIP_NONE);
    int Get_width() {return width_;}
    int Get_height() {return height_;}
    void SetText(const std::string& tmp_text) {text_val=tmp_text;}
    std::string GetText() {return text_val;}

private:
    std::string text_val;
    SDL_Color text_color;
    SDL_Texture* texture;
    int width_;
    int height_;
};


#endif // TEXT_H_INCLUDED
