
/*LOP XU LY MENU*/

#include "Menu.h"

Menu::Menu()
{
    action_ = SHOW_MENU;

    start_game_.SetText("START GAME");
    start_game_.Set_color(Text::WHITE_TEXT);

    advise_.SetText("INSTRUCTIONS");
    advise_.Set_color(Text::WHITE_TEXT);

    high_score.SetText("HIGH SCORE");
    high_score.Set_color(Text::WHITE_TEXT);

    exit_.SetText("EXIT");
    exit_.Set_color(Text::WHITE_TEXT);

    advise_content_.SetText("USE ARROW KEYS TO MOVE ");
    advise_content_.Set_color(Text::WHITE_TEXT);

    advise_content_2.SetText("Z= FIRE ATTACK, X= WATER ATTACK, P to pause");
    advise_content_2.Set_color(Text::WHITE_TEXT);

    your_score.SetText("YOUR SCORE");
    your_score.Set_color(Text::RED_TEXT);

    back_.SetText("BACK");
    back_.Set_color(Text::BLACK_TEXT);

    is_show_ = true;
    quit_game= false;
}

Menu::~Menu()
{

}

void Menu::Update_high_score(int x)
{
    std::ifstream input("high.txt");
    int a[7];
    memset(a,0,sizeof(a));
    int rank1, rank2, rank3, rank4, rank5;
    input>>a[1]>>a[2]>>a[3]>>a[4]>>a[5];
    a[6]=x;
    input.close();
    std::sort(a+1,a+7);
    rank1=a[6], rank2=a[5], rank3=a[4], rank4=a[3], rank5=a[2];
    std::ofstream output("high.txt");
    output<<rank1<<'\n'<<rank2<<'\n'<<rank3<<'\n'<<rank4<<'\n'<<rank5;
    output.close();
    std::string R1, R2, R3, R4, R5;
    R1= std::to_string(rank1);
    R2= std::to_string(rank2);
    R3= std::to_string(rank3);
    R4= std::to_string(rank4);
    R5= std::to_string(rank5);
    std::string H_list;
    H_list="Rank 1: "+R1+"   Rank 2: "+R2+"   Rank 3: "+R3+"   Rank 4: "+R4+"   Rank 5: "+R5;
    high_list.SetText(H_list);
}

void Menu::InitScore(int x)
{
    std::string Score= std::to_string(x);
    score.SetText(Score);
    score.Set_color(Text::WHITE_TEXT);
}

//CreateText duoc ke thua tu lop Text
void Menu::CreateText(TTF_Font * font, SDL_Renderer * screen)
{
    start_game_.CreateText(screen, font);
    advise_.CreateText(screen, font);
    high_score.CreateText(screen, font);
    exit_.CreateText(screen, font);
    advise_content_.CreateText(screen, font);
    advise_content_2.CreateText(screen, font);
    high_list.CreateText(screen,font);
    your_score.CreateText(screen,font);
    score.CreateText(screen,font);
    back_.CreateText(screen, font);
}

void Menu::SetPostionText()
{
    SDL_Rect menu_pos = this -> GetRect();

    start_game_.SetupRect(menu_pos.x + 550, menu_pos.y + 400);
    advise_.SetupRect(menu_pos.x + 540, menu_pos.y + 450);
    high_score.SetupRect(menu_pos.x+550, menu_pos.y+500);
    exit_.SetupRect(menu_pos.x + 600, menu_pos.y + 550);
    advise_content_.SetupRect(menu_pos.x + 200, menu_pos.y + 350);
    advise_content_2.SetupRect(menu_pos.x + 200, menu_pos.y + 400);
    high_list.SetupRect(menu_pos.x+200, menu_pos.y+350);
    your_score.SetupRect(menu_pos.x+560, menu_pos.y+300);
    score.SetupRect(menu_pos.x+600, menu_pos.y+350);
    back_.SetupRect(menu_pos.x + 600, menu_pos.y + 500);
}

void Menu::CheckEvents(SDL_Event events, SDL_Renderer* screen)
{
    int x = events.motion.x;
    int y = events.motion.y;
    if (action_ == SHOW_MENU)
    {
        //Kiem tra ve chuot khi focus
        if (SDLGeneralFunc::isInside(x, y, start_game_.GetRect()))
        {
            start_game_.Set_color(Text::RED_TEXT);
            if (events.motion.type == SDL_MOUSEBUTTONDOWN)
            {
                is_show_ = false;
            }
        }
        else
        {
            start_game_.Set_color(Text::WHITE_TEXT);
            if (SDLGeneralFunc::isInside(x, y, exit_.GetRect()))
            {
                exit_.Set_color(Text::RED_TEXT);
                if (events.motion.type == SDL_MOUSEBUTTONDOWN)
                {
                    quit_game=true;
                }
            }
            else
            {
                exit_.Set_color(Text::WHITE_TEXT);
                if (SDLGeneralFunc::isInside(x, y, advise_.GetRect()))
                {
                    advise_.Set_color(Text::RED_TEXT);
                    if (events.motion.type == SDL_MOUSEBUTTONDOWN)
                    {
                        action_ = SHOW_ADVISE;
                    }
                }
                else
                {
                    advise_.Set_color(Text::WHITE_TEXT);
                    if(SDLGeneralFunc::isInside(x,y,high_score.GetRect()))
                    {
                        high_score.Set_color(Text::RED_TEXT);
                        if(events.motion.type == SDL_MOUSEBUTTONDOWN)
                        {
                            action_=HIGH_SCORE;
                        }
                    }
                    else high_score.Set_color(Text::WHITE_TEXT);
                }
            }
        }
    }
    else if (action_ == SHOW_ADVISE)
    {
        if (SDLGeneralFunc::isInside(x, y, back_.GetRect()))
        {
            back_.Set_color(Text::RED_TEXT);
            if (events.motion.type == SDL_MOUSEBUTTONDOWN)
            {
                action_ = SHOW_MENU;
            }
        }
        else
        {
            back_.Set_color(Text::BLACK_TEXT);
        }
    }
    else if(action_==HIGH_SCORE)
    {
        if (SDLGeneralFunc::isInside(x, y, back_.GetRect()))
        {
            back_.Set_color(Text::RED_TEXT);
            if (events.motion.type == SDL_MOUSEBUTTONDOWN)
            {
                action_ = SHOW_MENU;
            }
        }
        else
        {
            back_.Set_color(Text::BLACK_TEXT);
        }
    }
    else if(action_==WIN||action_==LOSE)
    {
        if (SDLGeneralFunc::isInside(x, y, back_.GetRect()))
        {
            back_.Set_color(Text::RED_TEXT);
            if (events.motion.type == SDL_MOUSEBUTTONDOWN)
            {
                action_ = SHOW_MENU;
                MenuBackground(screen);
            }
        }
        else
        {
            back_.Set_color(Text::BLACK_TEXT);
        }
    }

}

void Menu::RenderMenu(SDL_Renderer * screen)
{
    switch (action_)
    {
    case SHOW_MENU:
    {
        Render(screen);
        start_game_.Render(screen);
        advise_.Render(screen);
        high_score.Render(screen);
        exit_.Render(screen);
        break;
    }
    case SHOW_ADVISE:
    {
        Render(screen);
        advise_content_.Render(screen);
        advise_content_2.Render(screen);
        back_.Render(screen);
        break;
    }
    case HIGH_SCORE:
    {
        Render(screen);
        high_list.Render(screen);
        back_.Render(screen);
        break;
    }
    case WIN:
    {
        Render(screen);
        your_score.Render(screen);
        score.Render(screen);
        back_.Render(screen);
        break;
    }
    case LOSE:
    {
        Render(screen);
        your_score.Render(screen);
        score.Render(screen);
        back_.Render(screen);
        break;
    }
    }
}

void Menu::MenuBackground(SDL_Renderer* screen)
{
    if(action_==LOSE) LoadImage("Images//lose.png",screen);
    else if(action_==WIN) LoadImage("Images//win.png",screen);
    else LoadImage("Images//menu.png",screen);
}
