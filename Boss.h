// lop boss
#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "GeneralFunc.h"
#include "BaseObj.h"
#include "Bullet.h"
#define FALLING_SPEED 0.8
#define LIMIT_SPEED 10
#define PLAYER_SPEED 10
#define JUMP_HEIGHT 18
#define BOSS_FRAME 20


class Boss : public baseObject
{
public:
    Boss();
    ~Boss();

    int health;
    int damage;
    bool player_visible;
    bool isFury;
    bool alive;

    enum WalkType
    {
        WALK_NONE = -1,
        WALK_R = 1,
        WALK_L = 0,
    };

    bool LoadImage(std::string, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clips();
    void Set_xPos(const float& x_pos) {xPos=x_pos;}
    void Set_yPos(const float& y_pos) {yPos=y_pos;}
    double Get_xPos() {return xPos;}
    void DoPlayer(Map &data);
    void CheckToMap(Map &data);
    void SetMapXY(int map_x, int map_y)
    {
        mapX=map_x;
        mapY=map_y;
    }
    void UpdatePlayerImg(SDL_Renderer* screen);
    void set_bullet_list(std::vector<Bullet*> bullet_list)
    {
        boss_bullet=bullet_list;
    }
    std::vector <Bullet*> Get_bullet_list()  {return boss_bullet;}
    void InitBullet(Bullet* t_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen);
    void Remove_bullet(const int& id);
    SDL_Rect GetBossRect();
private:
    std::vector <Bullet*> boss_bullet;
    double xVal, yVal, xPos, yPos;

    int width_frame, height_frame;

    SDL_Rect frame_clip[BOSS_FRAME];
    Input inputType;
    int frame_, status;
    bool on_ground;
    int mapX, mapY;
    int revive_time;
};

#endif // BOSS_H_INCLUDED
