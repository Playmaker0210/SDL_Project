// lop quan li nguoi choi
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GeneralFunc.h"
#include "BaseObj.h"
#include "Bullet.h"
#include "Menu.h"

#define FALLING_SPEED 0.8
#define LIMIT_SPEED 10
#define PLAYER_SPEED 10
#define JUMP_HEIGHT 18
#define PLAYER_FRAME 12
#define COIN 4
#define CRYSTAL 15
#define MANA 10
#define CLOSED_CHEST_1 11
#define OPENED_CHEST_1 12
#define CLOSED_CHEST_2 13
#define OPENED_CHEST_2 14
#define HP 16
#define STAR 17
#define WATER 18
#define FIRE 19


class Player : public baseObject
{
public:
    Player();
    ~Player();

    int health;
    int life;
    int mana;
    int score;
    int playing;
    enum WalkType
    {
        WALK_NONE = -1,
        WALK_R = 1,
        WALK_L = 0,
    };

    bool LoadImage(std::string, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clips();
    void HandleInput(SDL_Event events, SDL_Renderer* screen, Menu& t_menu);
    void DoPlayer(Map &data);
    void CheckToMap(Map &data);
    void SetMapXY(int map_x, int map_y)
    {
        mapX=map_x;
        mapY=map_y;
    }
    void CenterMap(Map &data);
    void UpdatePlayerImg(SDL_Renderer* screen);
    double Get_xPos() {return xPos;}
    void set_bullet_list(std::vector<Bullet*> bullet_list)
    {
        player_bullet=bullet_list;
    }
    std::vector <Bullet*> Get_bullet_list()  {return player_bullet;}
    void CheckBullet(Map& data, SDL_Renderer* screen);
    void IncreaseMana() {mana+=10;}
    void Remove_bullet(const int& id);
    SDL_Rect GetPlayerRect();
    void Set_Revive(const int& r_time) {revive_time= r_time;}
    void ItemProcess(Map &data, int x_pos, int y_pos);
    int Get_player_dmg(Bullet* t_bullet);
private:
    std::vector <Bullet*> player_bullet;
    double xVal, yVal, xPos, yPos;

    int width_frame, height_frame;

    SDL_Rect frame_clip[PLAYER_FRAME];
    Input inputType;
    int frame_, status;
    bool on_ground;
    int mapX, mapY;
    int revive_time;
    int money_count;
    bool isLeft;
    int power_level_fire;
    int power_level_water;
    int damage;
};


#endif // PLAYER_H_INCLUDED
