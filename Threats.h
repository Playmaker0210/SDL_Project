// lop quan li Threat
#ifndef THREATS_H_INCLUDED
#define THREATS_H_INCLUDED

#include "GeneralFunc.h"
#include "BaseObj.h"
#include "Bullet.h"
#include "Player.h"

#define THREATS_FRAME 10
#define THREATS_FALLING_SPEED 0.8
#define THREATS_LIMIT 10
#define THREATS_SPEED 10
#define THREAT_MOVE 3
class Threats: public baseObject
{
public:
    Threats();
    ~Threats();
    int health, damage;
    enum TypeMove
    {
        STATIC_THREAT=0,
        MOVE_IN_SPACE_THREAT=1,
    };

    void Set_xVal(const float& x_val) {xVal=x_val;}
    void Set_yVal(const float& y_val) {yVal=y_val;}
    void Set_xPos(const float& x_pos) {xPos=x_pos;}
    void Set_yPos(const float& y_pos) {yPos=y_pos;}
    float get_xPos() {return xPos;}
    float get_yPos() {return yPos;}
    void SetMapXY(const int& map_x, const int& map_y) {mapX=map_x; mapY=map_y;}
    void set_clips();
    bool LoadImage(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int Get_width_frame() {return width_frame;}
    int Get_height_frame() {return height_frame;}
    int Get_type_move() {return type_move;}
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);
    void Set_type_move(const int& typeMove) {type_move=typeMove;}
    void SetPos(const int& pos_A, const int& pos_B) {pos_a=pos_A; pos_b=pos_B;}
    void Set_input_left(const int& Left) {input_type.left_=Left;}
    void Imp_move_type(Map& data, SDL_Renderer* screen);
    std::vector<Bullet*> Get_bullet_list() {return threat_bullet;}
    void set_bullet_list(std::vector<Bullet*>& bullet_list) {threat_bullet=bullet_list;}
    void InitBullet(Bullet* t_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, Player& p_player);
    void Remove_bullet(const int& id);
    SDL_Rect GetThreatRect();
private:
    int width_frame, height_frame;
    int frame_;
    SDL_Rect frame_clip[THREATS_FRAME];
    bool on_ground;
    int revive_time;
    float xPos, yPos, xVal, yVal;
    int mapX, mapY;
    int type_move;
    int pos_a, pos_b;
    Input input_type;
    std::vector<Bullet*> threat_bullet;
    bool is_shoot;
    bool is_slash;
};

#endif // THREATS_H_INCLUDED
