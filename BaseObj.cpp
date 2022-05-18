#include "BaseObj.h"

baseObject::baseObject()
{
    picObject=NULL;
    rect_= {0,0,0,0};
}

baseObject::~baseObject()
{
    Reset();
}
//load ảnh
bool baseObject::LoadImage(std::string path, SDL_Renderer* screen)
{
    Reset();
    SDL_Texture* newTexture=NULL;
    SDL_Surface* loadSurface=IMG_Load(path.c_str());
    if(loadSurface!=NULL)
    {
        //xoá background của ảnh
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture= SDL_CreateTextureFromSurface(screen, loadSurface);
        if(newTexture!=NULL)
        {
            rect_.w=loadSurface->w;
            rect_.h=loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }
    picObject=newTexture;
    return picObject!=NULL;
}
//render ảnh
void baseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect Render_= {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(des,picObject,clip,&Render_);
}

void baseObject::Reset()
{
    if(picObject!=NULL)
    {
        SDL_DestroyTexture(picObject);
        picObject=NULL;
        rect_.w=0;
        rect_.h=0;
    }
}
