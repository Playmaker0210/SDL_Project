// xay dung lop dan ban
#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "GeneralFunc.h"
#include "BaseObj.h"

class Bullet : public baseObject
{
public:
    Bullet();
    ~Bullet();

    enum BulletDir
    {
        DIR_R=20,
        DIR_L=21,
        DIR_NONE=22,
    };

    enum BulletPower
    {
        DARK_BULLET=50,
        FIRE_BULLET=51,
        LIGHTNING_BULLET=52,
        BOSS_BULLET=53,
        WATER_BULLET=54,
    };

    void Set_xVal(const int& x_val) {xVal=x_val;}
    void Set_yVal(const int& y_val) {yVal=y_val;}
    int Get_xVal() {return xVal;}
    int Get_yVal() {return yVal;}
    void Set_is_move(const bool& isMove) {is_move=isMove;}
    bool Get_is_move() {return is_move;}
    void BulletMove(int pos,const int& y_border, int distance);
    void Set_bullet_dir(const unsigned int& bulletDir) {bullet_dir=bulletDir;}
    unsigned int Get_bullet_dir() {return bullet_dir;}
    void Set_bullet_type(const unsigned int& bulletType) {bullet_type= bulletType;}
    unsigned int Get_bullet_type() {return bullet_type;}
    bool Load_Img_Bullet(SDL_Renderer* screen, int level);

private:
    int xVal;
    int yVal;
    bool is_move;
    unsigned int bullet_dir;
    unsigned int bullet_type;
};


#endif // BULLET_H_INCLUDED
