#include "Threats.h"

Threats::Threats()
{
    width_frame=0;
    height_frame=0;
    xVal=0;
    yVal=0;
    xPos=0;
    yPos=0;
    on_ground=0;
    revive_time=0;
    frame_=0;
    pos_a=0;
    pos_b=0;
    input_type.left_=1;
    type_move=STATIC_THREAT;
    is_shoot=false;
    is_slash=false;
}

Threats::~Threats()
{

}

bool Threats::LoadImage(std::string path, SDL_Renderer* screen)
{
    bool ret=baseObject::LoadImage(path, screen);
    if(ret==true)
    {
        width_frame=rect_.w/THREATS_FRAME;
        height_frame=rect_.h;
    }
    return ret;
}

void Threats::set_clips()
{
    if(width_frame>0 && height_frame>0)
    {
        for(int i=0; i<THREATS_FRAME; i++)
        {
            frame_clip[i].x=i*width_frame;
            frame_clip[i].y=0;
            frame_clip[i].w=width_frame;
            frame_clip[i].h=height_frame;
        }
    }
}

void Threats::Show(SDL_Renderer* screen)
{
    if(revive_time==0)
    {
        rect_.x= xPos- mapX;
        rect_.y= yPos- mapY;
        frame_++;
        if(frame_>=THREATS_FRAME)
        {
            frame_=0;
        }
        SDL_Rect* current_clip= &frame_clip[frame_];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};
        SDL_RenderCopy(screen, picObject, current_clip, &renderQuad);
    }
}

void Threats::DoPlayer(Map& data)
{
    if(revive_time==0)
    {
        xVal=0;
        yVal+= THREATS_FALLING_SPEED;
        if(yVal>= THREATS_LIMIT)
        {
            yVal=THREATS_LIMIT;
        }
        if(type_move==MOVE_IN_SPACE_THREAT)
        {
            if(input_type.left_==1)
            {
                xVal-= THREAT_MOVE;
            }
            else if(input_type.right_==1)
            {
                xVal+= THREAT_MOVE;
            }
        }
        CheckToMap(data);
    }
}

void Threats::CheckToMap(Map& data)
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

            if((val1!=BLANK_TILE&& data.check_valid_tile[val1]==false)|| (val2!=BLANK_TILE&&data.check_valid_tile[val2]==false))
            {
                xPos=x2*TILE_SIZE;
                xPos-= width_frame+1;
                xVal=0;
            }
        }//di sang phai
        else if(xVal<0)
        {
            int val1=data.tile[y1][x1];
            int val2=data.tile[y2][x1];

            if((val1!=BLANK_TILE&& data.check_valid_tile[val1]==false)|| (val2!=BLANK_TILE&&data.check_valid_tile[val2]==false))
            {
                xPos=(x1+1)*TILE_SIZE;
                xVal=0;
            }
        }
    }//di sang trai

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

            if((val1!=BLANK_TILE&& data.check_valid_tile[val1]==false)|| (val2!=BLANK_TILE&&data.check_valid_tile[val2]==false))
            {
                yPos=y2*TILE_SIZE;
                yPos-= height_frame+1;
                yVal=0;
                on_ground=true;
            }
        }
        else if(yVal<0)
        {
            int val1=data.tile[y1][x1];
            int val2=data.tile[y1][x2];

            if((val1!=BLANK_TILE&& data.check_valid_tile[val1]==false)|| (val2!=BLANK_TILE&&data.check_valid_tile[val2]==false))
            {
                yPos=(y1+1)*TILE_SIZE;
                yVal=0;
            }
        }
    }
    xPos+=xVal;
    yPos+=yVal;
    if(xPos<0) xPos=0;
    else if(xPos+width_frame>data.max_x) xPos=data.max_x-width_frame-1;
}

void Threats::Imp_move_type(Map& data, SDL_Renderer* screen)
{
    if(type_move==MOVE_IN_SPACE_THREAT)
    {
        int X_=(xPos-1)/TILE_SIZE;
        int Y_=(yPos-1)/TILE_SIZE;
        if(on_ground==true)
        {
            if(data.tile[Y_][X_]!=0)
            {
                if(input_type.right_==1 && is_shoot==false)
                {
                    input_type.right_=0;
                    input_type.left_=1;
                    LoadImage("Images//threat_left.png",screen);
                }
                else if(input_type.left_==1 && is_shoot==false)
                {
                    input_type.left_=0;
                    input_type.right_=1;
                    LoadImage("Images//threat_right.png",screen);
                }
            }
            else
            {
                if(xPos >= pos_b && is_shoot==false)
                {
                    input_type.left_=1;
                    input_type.right_=0;
                    LoadImage("Images//threat_left.png",screen);
                }
                else if(xPos <= pos_a && is_shoot==false)
                {
                    input_type.left_=0;
                    input_type.right_=1;
                    LoadImage("Images//threat_right.png",screen);
                }
            }
        }
        else
        {
            if(input_type.left_==1)
            {
                LoadImage("Images//threat_left.png",screen);
            }
            else
            {
                LoadImage("Images//threat_right.png",screen);
            }
        }
    }
}

void Threats::InitBullet(Bullet* t_bullet, SDL_Renderer* screen)
{
    if(t_bullet!=NULL)
    {
        if(type_move==MOVE_IN_SPACE_THREAT) t_bullet->Set_bullet_type(Bullet::DARK_BULLET);
        else t_bullet->Set_bullet_type(Bullet::LIGHTNING_BULLET);
        t_bullet->Set_bullet_dir(Bullet::DIR_L);
        bool ret=t_bullet->Load_Img_Bullet(screen,1);
        if(ret==true)
        {
            t_bullet->Set_is_move(true);
            if(type_move==STATIC_THREAT) t_bullet->SetupRect(rect_.x+5,rect_.y+20);
            else t_bullet->SetupRect(rect_.x+5, rect_.y+35);
            t_bullet->Set_xVal(20);
            threat_bullet.push_back(t_bullet);
        }
    }
}

void Threats::MakeBullet(SDL_Renderer* screen, Player& p_player)
{
    for(int i=0; i<threat_bullet.size(); i++)
    {
        Bullet* tmp_bullet= threat_bullet.at(i);
        if(tmp_bullet!=NULL)
        {
            if(tmp_bullet->Get_is_move()==true)
            {
                int player_distance= p_player.GetRect().x - rect_.x;
                if(abs(player_distance)<=400&&on_ground==1)
                {
                    is_shoot=true;
                    if(player_distance<0)
                    {
                        tmp_bullet->Set_bullet_dir(Bullet::DIR_L);
                        if(type_move==STATIC_THREAT)
                        {
                            is_slash=true;
                            tmp_bullet->Load_Img_Bullet(screen,1);
                            LoadImage("Images//slash_left.png",screen);
                        }
                        else
                        {
                            input_type.right_=0;
                            input_type.left_=1;
                            if(rect_.x<=pos_a-mapX)
                            {
                                input_type.left_=0;
                                LoadImage("Images//threat_idle_left.png",screen);
                            }
                            else
                            {
                                LoadImage("Images//threat_left.png",screen);
                            }
                        }

                    }
                    else if(player_distance>0)
                    {
                        tmp_bullet->Set_bullet_dir(Bullet::DIR_R);
                        if(type_move==STATIC_THREAT)
                        {
                            is_slash=true;
                            tmp_bullet->Load_Img_Bullet(screen,1);
                            LoadImage("Images//slash_right.png",screen);
                        }

                        else
                        {
                            input_type.left_=0;
                            input_type.right_=1;
                            if(rect_.x>=pos_b-mapX)
                            {
                                input_type.right_=0;
                                LoadImage("Images//threat_idle_right.png",screen);
                            }
                            else
                            {
                                LoadImage("Images//threat_right.png",screen);
                            }
                        }
                    }
                    tmp_bullet->BulletMove(GetRect().x, SCREEN_HEIGHT,300);
                    tmp_bullet->Render(screen);
                }
                else
                {
                    is_shoot=false;
                    if(is_slash)
                    {
                        is_slash=false;
                        if(tmp_bullet->Get_bullet_dir()==Bullet::DIR_L)
                        {
                            LoadImage("Images//level_left.png",screen);
                        }
                        else if(tmp_bullet->Get_bullet_dir()==Bullet::DIR_R)
                        {
                            LoadImage("Images//level_right.png",screen);
                        }
                    }
                    tmp_bullet->Set_is_move(false);
                }
            }
            else
            {
                tmp_bullet->Set_is_move(true);
                if(type_move==STATIC_THREAT) tmp_bullet->SetupRect(rect_.x+5,rect_.y+20);
                else tmp_bullet->SetupRect(rect_.x+5, rect_.y+35);
            }
        }
    }
}

void Threats::Remove_bullet(const int& id)
{
    int bullet_size= threat_bullet.size();
    if(bullet_size>0 && id < bullet_size)
    {
        Bullet* tmp_bullet = threat_bullet.at(id);
        threat_bullet.erase(threat_bullet.begin()+id);
        if(tmp_bullet!=NULL)
        {
            delete tmp_bullet;
            tmp_bullet= NULL;
        }
    }
}

SDL_Rect Threats::GetThreatRect()
{
    SDL_Rect res;
    res.x=rect_.x;
    res.y=rect_.y;
    res.w=width_frame;
    res.h=height_frame;
    return res;
}
