// lop menu
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "GeneralFunc.h"
#include "Text.h"
#include "BaseObj.h"

class Menu : public baseObject
{
public:
    bool is_show_;
    bool quit_game;
    int action_;
    Text start_game_;
    Menu();
    ~Menu();

    void CreateText(TTF_Font* font, SDL_Renderer* screen);
    void SetPostionText();
    void RenderMenu(SDL_Renderer* des);
    void CheckEvents(SDL_Event events, SDL_Renderer* screen);
    void MenuBackground(SDL_Renderer* screen);
    void Update_high_score(int x);
    void InitScore(int x);
    enum ACTION_
    {
        SHOW_MENU=41,
        SHOW_ADVISE=42,
        HIGH_SCORE=43,
        QUIT=44,
        WIN=45,
        LOSE=46,
    };

private:

    Text advise_;
    Text high_score;
    Text exit_;

    Text advise_content_;
    Text advise_content_2;

    Text high_list;
    Text your_score;
    Text score;

    Text back_;

};

#endif // MENU_H_INCLUDED
