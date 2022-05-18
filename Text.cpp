#include "Text.h"

Text::Text()
{
    text_color.r=255;
    text_color.g=255;
    text_color.b=255;
}

Text::~Text()
{

}

bool Text::CreateText( SDL_Renderer* screen, TTF_Font* font)
{
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, text_val.c_str(), text_color);
	if(loadedSurface == NULL)
    {
        return false;
    }
	SetObject(SDL_CreateTextureFromSurface(screen, loadedSurface));
	if(this->GetTexture() == NULL)
    {
        return false;
    }
	this->SetWidthHeight(loadedSurface->w, loadedSurface->h);

	SDL_FreeSurface(loadedSurface);
	return true;
}

bool Text::Load_render_text(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* text_surface= TTF_RenderText_Solid(font,text_val.c_str(),text_color);
    if(text_surface)
    {
        texture= SDL_CreateTextureFromSurface(screen,text_surface);
        width_=text_surface->w;
        height_= text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return texture!= NULL;
}

void Text::Reset()
{
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture=NULL;
    }
}

void Text::Set_color(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color.r=red;
    text_color.g=green;
    text_color.b=blue;
}

void Text::Set_color(int type)
{
    if(type== RED_TEXT)
    {
        SDL_Color color= {255,0,0};
        text_color= color;
    }
    else if(type== WHITE_TEXT)
    {
        SDL_Color color= {255,255,255};
        text_color= color;
    }
    else if(type== BLACK_TEXT)
    {
        SDL_Color color= {0,0,0};
        text_color= color;
    }
}

void Text::Render_Text(SDL_Renderer* screen, int xPos, int yPos,
                       SDL_Rect* clip, double angle, SDL_Point* center,
                       SDL_RendererFlip flip)
{
    SDL_Rect renderQuad= {xPos, yPos, width_, height_};
    if(clip!=NULL)
    {
        renderQuad.w= clip->w;
        renderQuad.h= clip->h;
    }
    SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center ,flip);
}


