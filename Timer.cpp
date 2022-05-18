#include "Timer.h"
#include "GeneralFunc.h"
Timer::Timer()
{
    start_time=0;
    pause_time=0;
    is_pause_=false;
    is_start_=false;

}

Timer::~Timer()
{

}

void Timer::Start()
{
    is_start_=true;
    is_pause_=false;
    start_time=SDL_GetTicks();
}

void Timer::Stop()
{
    is_start_=false;
    is_pause_=false;
}


void Timer::Pause()
{
    if(is_start_==true && is_pause_==false)
    {
        is_pause_=true;
        pause_time=SDL_GetTicks()- start_time;
    }
}

void Timer::Resume()
{
    if(is_pause_==true)
    {
        is_pause_=true;
        start_time=SDL_GetTicks()- pause_time;
        pause_time=0;
    }
}

int Timer::Get_ticks()
{
    if(is_start_==true)
    {
        if(is_pause_==true) return pause_time;
        else return SDL_GetTicks()-start_time;
    }
    return 0;
}

bool Timer::Is_pause()
{
    return is_pause_;
}

bool Timer::Is_start()
{
    return is_start_;
}
