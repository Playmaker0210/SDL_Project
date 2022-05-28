// lop hien thi chi so cua nguoi choi len man hinh
#ifndef PLAYERSTAT_H_INCLUDED
#define PLAYERSTAT_H_INCLUDED

#include "GeneralFunc.h"
#include "BaseObj.h"

class PlayerStat : public baseObject
{
public:
    PlayerStat();
    ~PlayerStat();
    void SetNum(const int& num) {number_=num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);
    void Increase();
    void Decrease();

private:
    int number_;
    std::vector<int> pos_list;
};

class PlayerPower : public baseObject
{
public:
    PlayerPower();
    ~PlayerPower();
    void SetPos(const int& x, const int& y){x_pos=x; y_pos=y;}
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen, int type);

private:
     int x_pos, y_pos;
};

class Buff : public baseObject
{
public:
    Buff();
    ~Buff();
    void SetPos(const int& x, const int& y){x_pos=x; y_pos=y;}
    void Show(SDL_Renderer* screen, bool is_show);
    void Init(SDL_Renderer* screen, int type);
    bool is_show;

private:
     int x_pos, y_pos;
};

#endif // PLAYERSTAT_H_INCLUDED
