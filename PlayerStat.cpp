#include "PlayerStat.h"

PlayerStat::PlayerStat()
{
    number_=0;
}

PlayerStat::~PlayerStat()
{

}

void PlayerStat::AddPos(const int& xPos)
{
    pos_list.push_back(xPos);
}

void PlayerStat::Init(SDL_Renderer* screen)
{
    LoadImage("Images//player_life.png",screen);
    number_=3;
    if(pos_list.size()>0) pos_list.clear();
    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void PlayerStat::Show(SDL_Renderer* screen)
{
    for(int i=0; i<pos_list.size(); i++)
    {
        rect_.x=pos_list.at(i);
        rect_.y=0;
        Render(screen);
    }
}

void PlayerStat::Decrease()
{
    number_--;
    pos_list.pop_back();
}

void PlayerStat::Increase()
{
    number_++;
    int last_pos= pos_list.back();
    last_pos+=40;
    pos_list.push_back(last_pos);
}

PlayerPower::PlayerPower()
{
    x_pos=0;
    y_pos=0;
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::Init(SDL_Renderer* screen, int type)
{
    bool ret;
    if(type==1) ret=LoadImage("Images//player_health.png",screen);
    else ret=LoadImage("Images//player_mana.png",screen);
}

void PlayerPower::Show(SDL_Renderer* screen)
{
    rect_.x=x_pos;
    rect_.y=y_pos;
    Render(screen);
}

Buff::Buff()
{
    x_pos=0;
    y_pos=0;
}

Buff::~Buff()
{

}

void Buff::Init(SDL_Renderer* screen, int type)
{
    bool ret;
    if(type==1) ret=LoadImage("Images//staff.png",screen);
    else ret=LoadImage("Images//shield.png",screen);
}

void Buff::Show(SDL_Renderer* screen, bool is_show)
{
    if(is_show==true)
    {
        rect_.x=x_pos;
        rect_.y=y_pos;
        Render(screen);
    }
}
