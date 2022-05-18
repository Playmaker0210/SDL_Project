#include "Bullet.h"

Bullet::Bullet()
{
    xVal=0;
    yVal=0;
    is_move=false;
    bullet_dir=DIR_NONE;
    bullet_type=FIRE_BULLET;
}

Bullet::~Bullet()
{

}

void Bullet::BulletMove(int pos, const int& y_border, int distance)
{
    switch(bullet_dir)
    {
    case DIR_R:
    {
        rect_.x+= xVal;
        if(rect_.x>=(pos+distance))
        {
            is_move=false;
        }
    }
    break;
    case DIR_L:
    {
        rect_.x-=xVal;
        int checker = pos-  distance;
        if(checker <= 0) checker=0;
        if(rect_.x<checker)
        {
            is_move=false;
        }
    }
    break;
    }
}

bool Bullet::Load_Img_Bullet(SDL_Renderer* screen, int level)
{
    bool ret=false;
    switch (bullet_type)
    {
    case DARK_BULLET:
    {
        return LoadImage("Images//dark_bullet.png",screen);
    }
    break;
    case FIRE_BULLET:
    {
        if(level>3) level=3;
        std::string res = "Images//fire_bullet_" + std::to_string(level) + ".png";
        return LoadImage(res,screen);
    }
    break;
    case WATER_BULLET:
    {
        if(level>3) level=3;
        std::string res = "Images//water_bullet_" + std::to_string(level) + ".png";
        return LoadImage(res,screen);
    }
    break;
    case LIGHTNING_BULLET:
    {
        if(bullet_dir==DIR_L) return LoadImage("Images//lightning_left.png",screen);
        else if(bullet_dir==DIR_R) return LoadImage("Images//lightning_right.png", screen);
    }
    break;
    case BOSS_BULLET:
    {
        return LoadImage("Images//boss_bullet.png",screen);
    }
    break;
    }
    return ret;
}
