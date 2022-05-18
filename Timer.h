// xu li fps
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

class Timer
{
public:
    Timer();
    ~Timer();
    void Start();
    void Stop();
    void Pause();
    void Resume();

    int Get_ticks();

    bool Is_start();
    bool Is_pause();

private:
    int start_time;
    int pause_time;

    bool is_pause_;
    bool is_start_;
};



#endif // TIMER_H_INCLUDED
