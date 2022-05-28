#include "GeneralFunc.h"
#include "BaseObj.h"
#include "GameMap.h"
#include "Player.h"
#include "Timer.h"
#include "Threats.h"
#include "Explosion.h"
#include "Text.h"
#include "PlayerStat.h"
#include "Draw.h"
#include "Boss.h"
#include "Menu.h"

bool Init();
bool loadBackground(std::string path);
void Close();
bool MenuProcess();
bool GameProcess();
TTF_Font* font_time= NULL;
baseObject gameBackground;
Menu menu_game;

int main(int argc, char* argv[])
{
    if(Init()==false)
    {
        return -1;
    }
    menu_game.Update_high_score(0);
    while(1)
    {
        if(!MenuProcess()) return 0;
        if(!GameProcess()) return 0;
    }
    Close();
    return 0;
}

//Khoi tao cua so SDL
bool Init()
{
    bool success=true;
    int res=SDL_Init(SDL_INIT_VIDEO);
    if(res<0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    gameWindow=SDL_CreateWindow("Presented by PLAYMAKER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gameWindow==NULL)success = false;
    else
    {
        gameScreen=SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
        if(gameScreen==NULL) success= false;
        else
        {
            SDL_SetRenderDrawColor(gameScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags=IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&&imgFlags)) success=false;
        }
        if(TTF_Init()==-1) success=false;
        font_time = TTF_OpenFont("Font//Serif.ttf", 30);

    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096)==-1) success=false;
    else
    {
        g_sound_explo[0]=Mix_LoadWAV("Sound//fire_explo.wav");
        g_sound_explo[1]=Mix_LoadWAV("Sound//water_explo.wav");
        g_sound_explo[2]=Mix_LoadWAV("Sound//boss_explo.wav");
        g_sound_player[0]=Mix_LoadWAV("Sound//player_die.wav");
    }

    return success;
}

// load anh background
bool loadBackground(std::string path)
{
    bool res=gameBackground.LoadImage(path,gameScreen);
    if (res==false) return false;
    return true;
}

//tao vector chua Threat
std::vector<Threats*> MakeThreats()
{
    std::vector<Threats*> threats_list;
    Threats* threats_obj = new Threats [16];
    Threats* dynamic_threats = new Threats [10];

    //Threat di chuyen
    for(int i=0; i<10; i++)
    {
        Threats* tmp_threats = (dynamic_threats+i);
        if(tmp_threats!=NULL)
        {
            tmp_threats->health=20;
            tmp_threats->damage=10;
            tmp_threats->LoadImage("Images//threat_left.png",gameScreen);
            tmp_threats->set_clips();
            tmp_threats->Set_type_move(Threats::MOVE_IN_SPACE_THREAT);
            tmp_threats->Set_input_left(1);
            tmp_threats->Set_xPos(800+600*i);
            tmp_threats->Set_yPos(250);
            int pos1= tmp_threats->get_xPos()-2*TILE_SIZE;
            int pos2= pos1 + 4*TILE_SIZE;
            tmp_threats->SetPos(pos1,pos2);

            Bullet* tmp_bullet = new Bullet();
            tmp_threats->InitBullet(tmp_bullet,gameScreen);
            threats_list.push_back(tmp_threats);
        }
    }

    //Threat dung yen
    for(int i=0; i<16; i++)
    {
        Threats* tmp_threats = (threats_obj+i);
        if(tmp_threats!=NULL)
        {
            tmp_threats->health=30;
            tmp_threats->damage=5;
            tmp_threats->LoadImage("Images//level_left.png",gameScreen);
            tmp_threats->set_clips();
            tmp_threats->Set_yPos(250);
            tmp_threats->Set_xPos(450+i*1400);
            tmp_threats->Set_type_move(Threats::STATIC_THREAT);

            Bullet* tmp_bullet = new Bullet();
            tmp_threats->InitBullet(tmp_bullet,gameScreen);

            threats_list.push_back(tmp_threats);
        }
    }
    return threats_list;
}

// choi game
bool GameProcess()
{
    int last=1000000;
    int last_shield=1000000;
    int last_book=1000000;
    bool have_shield=false;
    bool have_book=false;
    std::vector<Threats*> MakeThreats();
    bool Quit=false;
    Timer fpsTimer;

    bool change_background=false;

    if(loadBackground("Images//background.png")==false)
    {
        return false;
    }

    GameMap game_map_ ;
    game_map_.LoadMap("Map/map01.dat");
    game_map_.LoadTiles(gameScreen);

    Player player_;
    player_.LoadImage("Images//player_right.png", gameScreen);
    player_.set_clips();

    PlayerStat player_life;
    player_life.Init(gameScreen);

    PlayerPower player_power[2];
    player_power[0].Init(gameScreen, 1);
    player_power[0].SetPos(200,0);
    player_power[1].Init(gameScreen, 2);
    player_power[1].SetPos(300,0);

    Buff player_buff[2];
    player_buff[0].Init(gameScreen, 1);
    player_buff[1].Init(gameScreen, 2);

    std::vector <Threats*> list_threats = MakeThreats();

    Boss gameBoss;
    gameBoss.LoadImage("Images//boss_idle.png",gameScreen);
    gameBoss.set_clips();
    Bullet* X_bullet = new Bullet();
    gameBoss.InitBullet(X_bullet,gameScreen);
    int xPosBoss=MAX_MAP_X*TILE_SIZE-SCREEN_WIDTH*0.2;
    gameBoss.Set_xPos(xPosBoss);
    gameBoss.Set_yPos(10);

    Explosion explo_threat[3];
    bool tRet = explo_threat[0].LoadImage("Images//fire_explo.png",gameScreen);
    bool tRet2 = explo_threat[1].LoadImage("Images//water_explo.png",gameScreen);
    bool tRet3 = explo_threat[2].LoadImage("Images//boss_explo.png",gameScreen);
    if(!tRet||!tRet2||!tRet3)
    {
        return false;
    }
    explo_threat[0].set_clip();
    explo_threat[1].set_clip();
    explo_threat[2].set_clip();

    Text manaText, hpText, scoText;
    manaText.Set_color(Text::WHITE_TEXT);
    hpText.Set_color(Text::RED_TEXT);
    scoText.Set_color(Text::BLACK_TEXT);
    while(!Quit)
    {
        fpsTimer.Start();
        while(SDL_PollEvent(&gameEvent)!=0)
        {
            if(gameEvent.type==SDL_QUIT) Quit=true;
            player_.HandleInput(gameEvent, gameScreen, menu_game);
        }

        // khi pause thi quay ve menu
        if(menu_game.is_show_)
        {
            if(!MenuProcess()) return false;
        }
        menu_game.start_game_.SetText("START GAME");

        SDL_SetRenderDrawColor(gameScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(gameScreen);

        gameBackground.Render(gameScreen, NULL);

        Map gameMap =game_map_.get_map();

        player_.CheckBullet(gameMap,gameScreen);
        player_.SetMapXY(gameMap.start_x, gameMap.start_y);
        player_.DoPlayer(gameMap);
        player_.Show(gameScreen);
        // khi hp cua nhan vat ve 0
        if(player_.health==0)
        {
            Mix_PlayChannel(-1, g_sound_player[0], 0);
            player_.life--;
            if(player_.life>0)
            {
                player_.health=100;
                player_.mana=150;
                player_.SetupRect(0,0);
                player_.Set_Revive(30);
                SDL_Delay(100);
                player_life.Decrease();
                player_life.Render(gameScreen);
            }
            else
            {
                menu_game.InitScore(player_.score);
                menu_game.Update_high_score(player_.score);
                player_.playing=-1;
                menu_game.action_=Menu::LOSE;
                menu_game.is_show_=true;
                return true;
            }
        }

        //khi nhan vat chien thang
        if(player_.playing==1)
        {
            player_.score+=player_.life*10000;
            menu_game.InitScore(player_.score);
            menu_game.Update_high_score(player_.score);
            menu_game.action_=Menu::WIN;
            menu_game.is_show_=true;
            return true;
        }

        game_map_.SetMap(gameMap);
        game_map_.DrawMap(gameScreen);

        //Ve hinh chu nhat
        Geometric rect_size(0,0,SCREEN_WIDTH,40);
        ColorData color_data(0, 80, 150);
        Draw::RenderRect(rect_size, color_data, gameScreen);

        Geometric outline_size(1,1,SCREEN_WIDTH-1,38);
        ColorData color_data2(255, 255, 255);
        Draw::RenderOutline(outline_size, color_data2,gameScreen);

        player_life.Show(gameScreen);
        player_power[0].Show(gameScreen);
        player_power[1].Show(gameScreen);

        bool alive=true;
        // duyet danh sach Threat kiem tra va cham giua nhan vat voi dan va Threat
        for(int i=0; i<list_threats.size(); i++)
        {
            Threats* tmp_threats= list_threats.at(i);
            if(tmp_threats!=NULL)
            {
                tmp_threats->SetMapXY(gameMap.start_x, gameMap.start_y);
                tmp_threats->Imp_move_type(gameMap, gameScreen);
                tmp_threats->DoPlayer(gameMap);
                tmp_threats->MakeBullet(gameScreen, player_ );
                tmp_threats->Show(gameScreen);

                SDL_Rect player_rect= player_.GetPlayerRect();
                bool bCol1= false;
                std::vector<Bullet*> tBullet_list = tmp_threats->Get_bullet_list();
                for(int j=0; j<tBullet_list.size(); j++)
                {
                    Bullet* tmp_bullet= tBullet_list.at(j);
                    if(tmp_bullet->Get_is_move()==true)
                    {
                        bCol1=SDLGeneralFunc::CheckCollision(tmp_bullet->GetRect(), player_rect);
                        if(bCol1)
                        {
                            if(player_.shield==false) player_.health= player_.health-tmp_threats->damage < 0 ? 0 : player_.health-tmp_threats->damage;
                            tmp_bullet->Set_is_move(false);
                            break;
                        }
                    }
                }
                SDL_Rect threat_rect= tmp_threats->GetThreatRect();
                bool bCol2=SDLGeneralFunc::CheckCollision(threat_rect, player_rect);
                if(bCol2) player_.health=0;
                if(player_.health==0)
                {
                    alive=false;
                    continue;
                }
            }
            if(alive==false) break;
        }

        int exp_frame_width= explo_threat[0].Get_width_frame();
        int exp_frame_height= explo_threat[0].Get_height_frame();
        int exp_boss_width= explo_threat[2].Get_width_frame();
        int exp_boss_height= explo_threat[2].Get_height_frame();
        // kiem tra su va cham giua dan cua nhan vat voi Threat va Boss, neu hp cua chung = 0 thi in ra anh vu no va phat am thanh
        std::vector <Bullet*> bullet_arr= player_.Get_bullet_list();
        for(int i=0; i<bullet_arr.size(); i++ )
        {
            Bullet* tmp_bullet = bullet_arr.at(i);
            if(tmp_bullet!=NULL)
            {
                for(int j=0; j<list_threats.size(); j++)
                {
                    Threats* tmp_threat= list_threats.at(j);
                    if(tmp_threat!=NULL)
                    {
                        SDL_Rect tmp_rect;
                        tmp_rect.x = tmp_threat->GetRect().x;
                        tmp_rect.y = tmp_threat->GetRect().y;
                        tmp_rect.w = tmp_threat->Get_width_frame();
                        tmp_rect.h = tmp_threat->Get_height_frame();

                        SDL_Rect tmp_rect2 = tmp_bullet->GetRect();
                        int bullet_type= tmp_bullet->Get_bullet_type();
                        bool bullet_col_threat= SDLGeneralFunc::CheckCollision(tmp_rect, tmp_rect2);
                        if(bullet_col_threat)
                        {
                            player_.Remove_bullet(i);
                            tmp_threat->health=tmp_threat->health-player_.Get_player_dmg(tmp_bullet) < 0 ? 0 : tmp_threat->health-player_.Get_player_dmg(tmp_bullet);
                            if(tmp_threat->health==0)
                            {
                                for(int k=0; k<EXPLO_FRAME; k++)
                                {
                                    int xPos= tmp_bullet->GetRect().x - exp_frame_width*0.5;
                                    int yPos= tmp_bullet->GetRect().y - exp_frame_height*0.5;
                                    if(bullet_type== Bullet::FIRE_BULLET)
                                    {
                                        explo_threat[0].set_frame(k);
                                        explo_threat[0].SetupRect(xPos, yPos);
                                        explo_threat[0].Show(gameScreen);
                                    }
                                    else
                                    {
                                        explo_threat[1].set_frame(k);
                                        explo_threat[1].SetupRect(xPos, yPos);
                                        explo_threat[1].Show(gameScreen);
                                    }

                                }
                                player_.score+=1000;
                                tmp_threat->Reset();
                                list_threats.erase(list_threats.begin()+j);
                                if(bullet_type== Bullet::FIRE_BULLET) Mix_PlayChannel(-1,g_sound_explo[0],0);
                                else Mix_PlayChannel(-1,g_sound_explo[1],0);
                            }
                        }
                        if(gameBoss.player_visible==true&&gameBoss.alive==true)
                        {
                            SDL_Rect boss_rect = gameBoss.GetBossRect();
                            bool bullet_col_boss= SDLGeneralFunc::CheckCollision(boss_rect, tmp_rect2);
                            if(bullet_col_boss)
                            {
                                player_.Remove_bullet(i);
                                gameBoss.health=gameBoss.health-player_.Get_player_dmg(tmp_bullet) < 0 ? 0 : gameBoss.health-player_.Get_player_dmg(tmp_bullet);
                                if(gameBoss.health==0)
                                {
                                    for(int k=0; k<EXPLO_FRAME; k++)
                                    {
                                        int xPos= tmp_bullet->GetRect().x - exp_boss_width*0.5;
                                        int yPos= tmp_bullet->GetRect().y - exp_boss_height*0.75;
                                        explo_threat[2].set_frame(k);
                                        explo_threat[2].SetupRect(xPos, yPos);
                                        explo_threat[2].Show(gameScreen);
                                    }
                                    player_.score+=20000;
                                    Mix_PlayChannel(1,g_sound_explo[2],0);
                                    gameBoss.alive=false;
                                    gameBoss.Reset();
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }

        // thoi gian cua game
        std::string gTime= "";
        Uint32 time_val= SDL_GetTicks()/ 1000;
        Uint32 gameTime= 1000000- time_val;
        if(gameTime%3==0&&last!=gameTime)
        {
            player_.mana=player_.mana+10<150 ? player_.mana+10 : 150;
            last=gameTime;
        }
        if(player_.shield==true&&have_shield==false)
        {
            last_shield= gameTime;
            have_shield=true;
            if(have_book) player_buff[1].SetPos(SECOND_POS, 0);
            else player_buff[1].SetPos(FIRST_POS, 0);
        }
        if(player_.shield==true&&last_shield-gameTime==5)
        {
            have_shield=false;
            player_.shield=false;
            last_shield=1000000;
            player_buff[1].SetPos(0,0);
        }
        if(player_.book==true&&have_book==false)
        {
            last_book= gameTime;
            have_book=true;
            if(have_shield) player_buff[0].SetPos(SECOND_POS, 0);
            else player_buff[0].SetPos(FIRST_POS, 0);
        }
        if(player_.book==true&&last_book-gameTime==5)
        {
            have_book=false;
            player_.book=false;
            player_.attack_bonus=0;
            last_book=1000000;
            player_buff[1].SetPos(0,0);
        }
        player_buff[0].Show(gameScreen, player_.book);
        player_buff[1].Show(gameScreen, player_.shield);
        std::string str_val= std::to_string(player_.mana);
        gTime+= str_val;
        manaText.SetText(gTime);
        manaText.Load_render_text(font_time, gameScreen);
        manaText.Render_Text(gameScreen, 340, 0);

        //hien thi hp
        std::string gHP= "";
        std::string hp_val= std::to_string(player_.health);
        gHP+= hp_val;
        hpText.SetText(gHP);
        hpText.Load_render_text(font_time, gameScreen);
        hpText.Render_Text(gameScreen, 240, 0);

        // hien thi diem
        std::string gSco="Point: ";
        std::string sco_val= std::to_string(player_.score);
        gSco+= sco_val;
        scoText.SetText(gSco);
        scoText.Load_render_text(font_time, gameScreen);
        scoText.Render_Text(gameScreen, SCREEN_WIDTH-400,0);

        //hien thi boss
        int val= MAX_MAP_X*TILE_SIZE-(gameMap.start_x+player_.GetPlayerRect().x);
        if(val<=SCREEN_WIDTH)
        {
            if(change_background==false)
            {
                change_background=true;
                loadBackground("Images//background_boss.png");
            }
            gameBoss.SetMapXY(gameMap.start_x, gameMap.start_y);
            gameBoss.DoPlayer(gameMap);
            if(gameBoss.player_visible==false&&(double) xPosBoss-player_.Get_xPos()<=5*TILE_SIZE)
            {
                game_map_.Format();
                gameBoss.player_visible=true;
                gameBoss.UpdatePlayerImg(gameScreen);
            }
            if(gameBoss.health<=250&&gameBoss.isFury==false)
            {
                gameBoss.isFury=true;
                gameBoss.damage=40;
                gameBoss.UpdatePlayerImg(gameScreen);
            }
            gameBoss.MakeBullet(gameScreen);
            SDL_Rect player_rect= player_.GetPlayerRect();
            //kiem tra va cham giua nhan vat voi dan cua boss
            bool bCol1= false;
            std::vector<Bullet*> tBullet_list = gameBoss.Get_bullet_list();
            for(int j=0; j<tBullet_list.size(); j++)
            {
                Bullet* tmp_bullet= tBullet_list.at(j);
                if(tmp_bullet->Get_is_move()==true)
                {
                    bCol1=SDLGeneralFunc::CheckCollision(tmp_bullet->GetRect(), player_rect);
                    if(bCol1)
                    {
                        player_.health= player_.health-gameBoss.damage < 0 ? 0 : player_.health-gameBoss.damage;
                        tmp_bullet->Set_is_move(false);
                        break;
                    }
                }
            }
            SDL_Rect threat_rect= gameBoss.GetBossRect();
            bool bCol2=SDLGeneralFunc::CheckCollision(threat_rect, player_rect);
            if(bCol2&&gameBoss.alive==true) player_.health=0;
            if(player_.health==0)
            {
                alive=false;
                continue;
            }
            gameBoss.Show(gameScreen);
        }

        // xu li fps
        SDL_RenderPresent(gameScreen);
        int real_time = fpsTimer.Get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND ;// 1000 ms
        if(real_time < time_one_frame)
        {
            int delay_time= time_one_frame - real_time;
            if(delay_time>=0) SDL_Delay(delay_time);
        }
    }

    //xoa vector Threat
    player_.Reset();
    explo_threat[0].Reset();
    explo_threat[1].Reset();
    explo_threat[2].Reset();
    player_life.Reset();
    player_power[0].Reset();
    player_power[1].Reset();
    manaText.Reset();
    scoText.Reset();
    hpText.Reset();
    for(int i=0; i<list_threats.size(); i++)
    {
        Threats* tmp_threat= list_threats.at(i);
        if(tmp_threat!=NULL)
        {
            tmp_threat->Reset();
            tmp_threat=NULL;
        }
    }
    list_threats.clear();
}

void Close()
{
    gameBackground.Reset();
    SDL_DestroyRenderer(gameScreen);
    gameScreen=NULL;
    SDL_DestroyWindow(gameWindow);
    gameWindow=NULL;
    IMG_Quit();
    SDL_Quit();
}

bool MenuProcess()
{
    menu_game.MenuBackground(gameScreen);
    menu_game.SetPostionText();
    while(menu_game.is_show_)
    {
        while(SDL_PollEvent(&gameEvent)!=0)
        {
            if(gameEvent.type == SDL_QUIT)
            {
                menu_game.is_show_ = false;
                Close();
                return false;
            }
            menu_game.CheckEvents(gameEvent,gameScreen);
            if(menu_game.quit_game)
            {
                Close();
                return false;
            }
        }
        SDL_SetRenderDrawColor(gameScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,
                               RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        menu_game.CreateText(font_time, gameScreen);
        menu_game.RenderMenu(gameScreen);
        SDL_RenderPresent(gameScreen);
        SDL_Delay(150);
    }
    return true;
}

