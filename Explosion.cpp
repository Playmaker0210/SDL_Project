#include "Explosion.h"

Explosion::Explosion()
{
    width_frame=0;
    height_frame=0;
    frame_=0;
}

Explosion::~Explosion()
{

}

bool Explosion::LoadImage(std::string path, SDL_Renderer* screen)
{
    bool ret= baseObject::LoadImage(path, screen);

    if(ret)
    {
        width_frame= rect_.w/ EXPLO_FRAME;
        height_frame= rect_.h;
    }
    return ret;
}

void Explosion::set_clip()
{
    if(width_frame>0 && height_frame>0)
    {
        for(int i=0; i<EXPLO_FRAME; i++)
        {
            frame_clip[i].x=i*width_frame;
            frame_clip[i].y=0;
            frame_clip[i].w=width_frame;
            frame_clip[i].h=height_frame;
        }
    }
}

void Explosion::Show(SDL_Renderer* screen)
{
    SDL_Rect* current_clip= &frame_clip[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};

    if(current_clip!=NULL)
    {
        renderQuad.w=current_clip->w;
        renderQuad.h=current_clip->h;
    }
    SDL_RenderCopy(screen, picObject, current_clip, &renderQuad);
}
