// lop quan li vu no
#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "BaseObj.h"

#define EXPLO_FRAME 10

class Explosion : public baseObject
{
public:
    Explosion();
    ~Explosion();

    void set_clip();
    void set_frame(const int& fra) {frame_=fra;}
    bool LoadImage(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int Get_width_frame() {return width_frame;}
    int Get_height_frame() {return height_frame;}

private:
    int width_frame;
    int height_frame;
    int frame_;
    SDL_Rect frame_clip[EXPLO_FRAME];
};

#endif // EXPLOSION_H_INCLUDED
