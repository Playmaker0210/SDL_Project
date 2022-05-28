#include "Player.h"
#include "GameMap.h"

Player::Player()
{
    frame_=0;
    xPos=0, yPos=0, xVal=0, yVal=0;
    width_frame=0;
    height_frame=0;
    status=WALK_NONE;
    inputType= {0,0,0,0,0,0};
    on_ground=false;
    mapX=0;
    mapY=0;
    revive_time=0;
    money_count=0;
    health=100;
    life=3;
    mana=150;
    isLeft=false;
    score=0;
    power_level_fire=1;
    power_level_water=1;
    playing=0;
    shield=false;
    book = false;
    attack_bonus=0;
    g_sound_player[1]=Mix_LoadWAV("Sound//get_item.wav");
}

Player::~Player()
{

}

bool Player::LoadImage(std::string path, SDL_Renderer* screen)
{
    bool ret= baseObject::LoadImage(path, screen);
    if(ret==true)
    {
        width_frame=rect_.w/PLAYER_FRAME; //lay chieu rong cua 1 frame tren anh dong
        height_frame=rect_.h;
    }
    return ret;
}

void Player::set_clips()
{
    if(width_frame>0 && height_frame>0)
    {
        for(int i=0; i<PLAYER_FRAME; i++)
        {
            frame_clip[i].x=i*width_frame;
            frame_clip[i].y=0;
            frame_clip[i].w=width_frame;
            frame_clip[i].h=height_frame;
        }
    }
}

void Player::Show(SDL_Renderer* screen)
{
    UpdatePlayerImg(screen);
    if(inputType.left_==1||inputType.right_==1||inputType.shooting_==1) frame_++;
    else frame_=0;
    if(frame_>=PLAYER_FRAME) frame_=0;
    if(revive_time==0)
    {
        rect_.x=xPos-mapX;
        rect_.y=yPos-mapY;

        SDL_Rect* current_clip= &frame_clip[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};
        SDL_RenderCopy(screen, picObject, current_clip, &renderQuad);
    }

}

void Player::HandleInput(SDL_Event events, SDL_Renderer* screen, Menu& t_menu)
{
    if(events.type==SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            status=WALK_R;
            inputType.right_=1;
            inputType.left_=0;
            UpdatePlayerImg(screen);
        }
        break;
        case SDLK_LEFT :
        {
            status=WALK_L;
            inputType.left_=1;
            inputType.right_=0;
            UpdatePlayerImg(screen);
        }
        break;
        case SDLK_UP :
        {
            if(inputType.left_==0&&inputType.right_==0) inputType.jump_=1;
            UpdatePlayerImg(screen);
        }
        break;
        case SDLK_z:
        {
            if(mana>=15)
            {
                inputType.shooting_=1;
                mana-=15;
                Bullet* p_bullet = new Bullet();
                p_bullet->Set_bullet_type(Bullet::FIRE_BULLET);
                p_bullet->Load_Img_Bullet(screen, power_level_fire);
                p_bullet->Set_xVal(20);
                p_bullet->Set_yVal(20);
                p_bullet->Set_is_move(true);
                //UpdatePlayerImg(screen);
                if(status==WALK_L)
                {
                    p_bullet->Set_bullet_dir(Bullet::DIR_L);
                    p_bullet->SetupRect(this->rect_.x, rect_.y+height_frame*0.23);
                }
                else if(status==WALK_R)
                {
                    p_bullet->Set_bullet_dir(Bullet::DIR_R);
                    p_bullet->SetupRect(this->rect_.x+width_frame-20, rect_.y+height_frame*0.23);
                }
                UpdatePlayerImg(screen);
                player_bullet.push_back(p_bullet);
            }
            else inputType.shooting_=0;
        }
        break;
        case SDLK_x:
        {
            if(mana>=10)
            {
                inputType.shooting_=1;
                mana-=10;
                Bullet* p_bullet = new Bullet();
                p_bullet->Set_bullet_type(Bullet::WATER_BULLET);
                p_bullet->Load_Img_Bullet(screen, power_level_water);
                p_bullet->Set_xVal(20);
                p_bullet->Set_yVal(20);
                p_bullet->Set_is_move(true);
                //UpdatePlayerImg(screen);
                if(status==WALK_L)
                {
                    p_bullet->Set_bullet_dir(Bullet::DIR_L);
                    p_bullet->SetupRect(this->rect_.x, rect_.y+height_frame*0.23);
                }
                else if(status==WALK_R)
                {
                    p_bullet->Set_bullet_dir(Bullet::DIR_R);
                    p_bullet->SetupRect(this->rect_.x+width_frame-20, rect_.y+height_frame*0.23);
                }
                UpdatePlayerImg(screen);
                player_bullet.push_back(p_bullet);
            }
            else inputType.shooting_=0;
        }
        break;
        case SDLK_p:
        {
            t_menu.is_show_=true;
            t_menu.start_game_.SetText("RESUME GAME");
        }
        }
    }
    else if(events.type==SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            inputType.right_=0;
        }
        break;
        case SDLK_LEFT :
        {
            inputType.left_=0;
        }
        break;
        case SDLK_z:
        {
            inputType.shooting_=0;
        }
        case SDLK_x:
        {
            inputType.shooting_=0;
        }
        break;
        }
    }
}

void Player::CheckBullet(Map& data, SDL_Renderer* screen)
{
    for(int i=0; i<player_bullet.size(); i++)
    {
        Bullet* p_bullet=player_bullet.at(i);
        if(p_bullet!=NULL)
        {
            if(p_bullet->Get_is_move()==true)
            {
                p_bullet->BulletMove(GetRect().x, SCREEN_HEIGHT, 300);
                p_bullet->Render(screen);
            }
            else
            {
                player_bullet.erase(player_bullet.begin()+i);
                if(p_bullet!=NULL)
                {
                    p_bullet=NULL;
                    delete p_bullet;
                }
            }
        }
        else
        {
            player_bullet.erase(player_bullet.begin()+i);
            if(p_bullet!=NULL)
            {
                p_bullet=NULL;
                delete p_bullet;
            }
        }
    }
}
void Player::DoPlayer(Map& data)
{
    if(revive_time==0)
    {
        xVal=0;
        yVal+=FALLING_SPEED; //toc do roi

        if(yVal>=LIMIT_SPEED)
        {
            yVal=LIMIT_SPEED;
        }
        if(inputType.left_==1)
        {
            xVal-=PLAYER_SPEED;
        }
        else if(inputType.right_==1)
        {
            xVal+=PLAYER_SPEED;
        }
        if(inputType.jump_==1)
        {
            if(on_ground==true) yVal = -JUMP_HEIGHT; //neu -= thi se di tu tu len
            inputType.jump_=0;
            on_ground=false;
        }
        CheckToMap(data);
        CenterMap(data);
    }
    if(revive_time>0)
    {
        revive_time--;
        if(revive_time==0)
        {
            //on_ground=false;
            if(xPos>256)
            {
                xPos-=256;
            }
            else xPos=0;
            yPos=0;
            xVal=0;
            yVal=0;
        }
    }
}

void Player::CheckToMap(Map& data)
{
    int x1=0, x2=0, y1=0, y2=0; //xet tu vi tri 1 den 2 theo x, y
    // kiem tra theo x
    int height_min= height_frame < TILE_SIZE ? height_frame : TILE_SIZE ;
    //tim toa do o
    x1=(xPos+xVal)/TILE_SIZE;
    x2=(xPos+xVal+width_frame-1)/TILE_SIZE;

    y1=yPos/TILE_SIZE;
    y2=(yPos+height_min-1)/TILE_SIZE;

    if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if(xVal>0)
        {
            int val1=data.tile[y1][x2];
            int val2=data.tile[y2][x2];

            if(data.check_valid_tile[val1]==true || data.check_valid_tile[val2]==true)
            {
                ItemProcess(data, x2, y1);
                ItemProcess(data, x2, y2);
            }
            else
            {
                if(val1!=BLANK_TILE || val2!=BLANK_TILE)
                {
                    xPos=x2*TILE_SIZE;
                    xPos-= width_frame+1;
                    xVal=0;
                }
            }
        }//di sang phai
        else if(xVal<0)
        {
            int val1=data.tile[y1][x1];
            int val2=data.tile[y2][x1];

            if(data.check_valid_tile[val1]==true || data.check_valid_tile[val2]==true)
            {
                ItemProcess(data, x1, y1);
                ItemProcess(data, x1, y2);
            }
            else
            {
                if(val1!=BLANK_TILE || val2!=BLANK_TILE)
                {
                    xPos=(x1+1)*TILE_SIZE;
                    xVal=0;
                }
            }

        }//di sang trai
    }

    //kiem tra theo y
    int width_min = width_frame<TILE_SIZE ? width_frame : TILE_SIZE ;

    x1=xPos/TILE_SIZE;
    x2=(xPos+width_min)/TILE_SIZE;

    y1=(yPos+yVal)/TILE_SIZE;
    y2=(yPos+yVal+height_frame-1)/TILE_SIZE;

    if(x1>=0 && x2<MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y)
    {
        if(yVal>0)
        {
            int val1=data.tile[y2][x1];
            int val2=data.tile[y2][x2];

            if(data.check_valid_tile[val1]==true || data.check_valid_tile[val2]==true)
            {
                ItemProcess(data, x1, y2);
                ItemProcess(data, x2, y2);
            }
            else
            {
                if(val1!=BLANK_TILE || val2!=BLANK_TILE)
                {
                    yPos=y2*TILE_SIZE;
                    yPos-= height_frame+1;
                    yVal=0;
                    if(status==WALK_NONE) status=WALK_R;
                    on_ground=true;
                }
            }
        }
        else if(yVal<0)
        {
            int val1=data.tile[y1][x1];
            int val2=data.tile[y1][x2];

            if(data.check_valid_tile[val1]==true || data.check_valid_tile[val2]==true)
            {
                ItemProcess(data, x1, y1);
                ItemProcess(data, x2, y1);
            }
            else
            {
                if(val1!=BLANK_TILE||val2!=BLANK_TILE)
                {
                    yPos=(y1+1)*TILE_SIZE;
                    yVal=0;
                }
            }
        }
    }
    xPos+=xVal;
    yPos+=yVal;
    if(xPos<0) xPos=0;
    else if(xPos+width_frame>data.max_x) xPos=data.max_x-width_frame-1;
}

void Player::CenterMap(Map& data)
{
    // kiem tra giua ban do theo chieu x
    data.start_x= xPos-(SCREEN_WIDTH/2);
    if(data.start_x<0) data.start_x=0;
    else if(data.start_x + SCREEN_WIDTH >= data.max_x)
    {
        data.start_x= data.max_x-SCREEN_WIDTH;
    }

    // kiem tra giua ban do theo chieu y
    data.start_y= yPos-(SCREEN_HEIGHT/2);
    if(data.start_y<0) data.start_y=0;
    else if(data.start_y + SCREEN_HEIGHT >= data.max_y)
    {
        data.start_y= data.max_y-SCREEN_HEIGHT;
    }
    if(yPos>data.max_y)
    {
        health=0;
        revive_time=30;
    }
}

//cap nhat anh cho tung truong hop
void Player::UpdatePlayerImg(SDL_Renderer* screen)
{
    //std::cout<<on_ground<<" "<<inputType.shooting_<<" "<<status<<'\n';
    if(inputType.shooting_==1)
    {
        if(status==WALK_L) LoadImage("Images//shoot_left.png",screen);
        else LoadImage("Images//shoot_right.png",screen);
    }
    else
    {
        if(on_ground==true)
        {
            if(status==WALK_L) LoadImage("Images//player_left.png",screen);
            else LoadImage("Images//player_right.png",screen);
        }
        else
        {
            if(status==WALK_L) LoadImage("Images//jump_left.png",screen);
            else LoadImage("Images//jump_right.png",screen);
        }
    }
}

void Player::Remove_bullet(const int& id)
{
    int bullet_size= player_bullet.size();
    if(bullet_size>0 && id < bullet_size)
    {
        Bullet* tmp_bullet = player_bullet.at(id);
        player_bullet.erase(player_bullet.begin()+id);
        if(tmp_bullet!=NULL)
        {
            delete tmp_bullet;
            tmp_bullet= NULL;
        }
    }
}

SDL_Rect Player::GetPlayerRect()
{
    SDL_Rect res;
    res.x=rect_.x;
    res.y=rect_.y;
    res.w=width_frame;
    res.h=height_frame;
    return res;
}

void Player::ItemProcess(Map &data, int x_pos, int y_pos)
{
    if(data.check_valid_tile[data.tile[y_pos][x_pos]]==false) return;
    switch(data.tile[y_pos][x_pos])
    {
    case COIN:
        {
            score+=100;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case CRYSTAL:
        {
            score+=1000;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case MANA:
        {
            mana=mana+50 < 150 ? mana+50 : 150;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case CLOSED_CHEST_1:
        {
            score+=500;
            data.tile[y_pos][x_pos]=OPENED_CHEST_1;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case CLOSED_CHEST_2:
        {
            score+=5000;
            data.tile[y_pos][x_pos]=OPENED_CHEST_2;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case HP:
        {
            health=health+50<100 ? health+50 : 100;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case WATER:
        {
            power_level_water++;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case FIRE:
        {
            power_level_fire++;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case STAR:
        {
            playing=1;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case SHIELD:
        {
            shield=true;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
        break;
    case BOOK:
        {
            book=true;
            attack_bonus=100;
            data.tile[y_pos][x_pos]=0;
            Mix_PlayChannel(-1,g_sound_player[1],0);
        }
    }
}

int Player::Get_player_dmg(Bullet* t_bullet)
{
    if(t_bullet->Get_bullet_type()==Bullet::FIRE_BULLET) return (15+attack_bonus+power_level_fire*5);
    return (10+attack_bonus+power_level_water*5);
}
