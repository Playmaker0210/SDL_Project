//lop doi tuong co ban
#ifndef BaseObj_H_INCLUDED
#define BaseObj_H_INCLUDED

#include "GeneralFunc.h"

class baseObject
{
public:
    baseObject();
    ~baseObject();
    void SetupRect(const int &x, const int &y)
    {
        rect_.x=x;
        rect_.y=y;
    }
    SDL_Rect GetRect()
    {
        return rect_;
    }
    void SetObject(SDL_Texture* object) {picObject = object;}
    SDL_Texture* GetTexture () const
    {
        return picObject;
    }
    void SetWidthHeight(const int& w,const int& h) {rect_.w = w; rect_.h = h;}
    virtual bool LoadImage(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip=NULL);
    void Reset();

protected:
    SDL_Texture* picObject;
    SDL_Rect rect_;
};

#endif // BaseObj_H_INCLUDED
