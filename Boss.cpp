#include "Boss.h"
#include "GameMap.h"

Boss::Boss()
{
    frame_=0;
    xPos=0, yPos=0, xVal=0, yVal=0;
    width_frame=0;
    height_frame=0;
    on_ground=false;
    mapX=0;
    mapY=0;
    revive_time=0;
    health=500;
    player_visible=false;
    isFury=false;
    alive=true;
    damage=15;
    g_sound_boss=Mix_LoadWAV("Sound//boss_sound.wav");
}

Boss::~Boss()
{

}

bool Boss::LoadImage(std::string path, SDL_Renderer* screen)
{
    bool ret= baseObject::LoadImage(path, screen);
    if(ret==true)
    {
        width_frame=rect_.w/BOSS_FRAME; //lay chieu rong cua 1 frame tren anh dong
        height_frame=rect_.h;
    }
    return ret;
}

void Boss::set_clips()
{
    if(width_frame>0 && height_frame>0)
    {
        for(int i=0; i<BOSS_FRAME; i++)
        {
            frame_clip[i].x=i*width_frame;
            frame_clip[i].y=0;
            frame_clip[i].w=width_frame;
            frame_clip[i].h=height_frame;
        }
    }
}

void Boss::Show(SDL_Renderer* screen)
{
    if(revive_time==0)
    {
        rect_.x= xPos- mapX;
        rect_.y= yPos- mapY;
        frame_++;
        if(frame_>=BOSS_FRAME)
        {
            frame_=0;
        }
        SDL_Rect* current_clip= &frame_clip[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};
        SDL_RenderCopy(screen, picObject, current_clip, &renderQuad);
    }
}




void Boss::DoPlayer(Map& data)
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

void Boss::CheckToMap(Map& data)
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
                data.tile[y1][x2]=0;
                data.tile[y2][x2]=0;
                //IncreaseMana();
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
                data.tile[y1][x1]=0;
                data.tile[y2][x1]=0;
                //IncreaseMana();
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
                data.tile[y2][x1]=0;
                data.tile[y2][x2]=0;
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
                data.tile[y1][x1]=0;
                data.tile[y1][x2]=0;
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

void Boss::InitBullet(Bullet* t_bullet, SDL_Renderer* screen)
{
    if(t_bullet!=NULL&&alive==true)
    {
        t_bullet->Set_bullet_type(Bullet::BOSS_BULLET);
        t_bullet->Set_bullet_dir(Bullet::DIR_L);
        bool ret=t_bullet->Load_Img_Bullet(screen,1);
        if(ret==true)
        {
            t_bullet->Set_is_move(true);
            t_bullet->SetupRect(rect_.x+10, rect_.y+192);
            t_bullet->Set_xVal(20);
            boss_bullet.push_back(t_bullet);
        }
    }
}

void Boss::MakeBullet(SDL_Renderer* screen)
{
    if(alive==false) return;
    for(int i=0; i<boss_bullet.size(); i++)
    {
        Bullet* tmp_bullet= boss_bullet.at(i);
        if(tmp_bullet!=NULL&&player_visible==true)
        {
            if(tmp_bullet->Get_is_move()==true)
            {
                Mix_PlayChannel(-1,g_sound_boss,0);
                tmp_bullet->BulletMove(GetRect().x, SCREEN_HEIGHT, SCREEN_WIDTH);
                tmp_bullet->Render(screen);
            }
            else
            {
                tmp_bullet->Set_is_move(true);
                tmp_bullet->SetupRect(rect_.x+10, rect_.y+192);
            }
        }
    }
}

//cap nhat anh cho tung truong hop
void Boss::UpdatePlayerImg(SDL_Renderer* screen)
{
    if(isFury==true) LoadImage("Images//boss_fury.png",screen);
    else if(player_visible==true) LoadImage("Images//boss_attack.png",screen);
    else if(player_visible==false) LoadImage("Images//boss_idle.png",screen);
}

SDL_Rect Boss::GetBossRect()
{
    SDL_Rect res;
    res.x=rect_.x;
    res.y=rect_.y;
    res.w=width_frame;
    res.h=height_frame;
    return res;
}
