// cac ham chung
#ifndef GeneralFunc_H_INCLUDED
#define GeneralFunc_H_INCLUDED
#include <windows.h>
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* gameWindow = NULL ;
static SDL_Renderer* gameScreen = NULL ;
static SDL_Event gameEvent ;
static Mix_Chunk* g_sound_explo[3];
static Mix_Chunk* g_sound_player[2];
static Mix_Chunk* g_sound_boss;

// Thong so man hinh
const int SCREEN_WIDTH = 1280 ;
const int SCREEN_HEIGHT = 640 ;
const int BIT_PER_PIXEL = 32 ;
const int FRAME_PER_SECOND = 25;

const int COLOR_KEY_R = 167 ;
const int COLOR_KEY_G = 175 ;
const int COLOR_KEY_B = 180 ;
const int RENDER_DRAW_COLOR = 255;

//Thong so map
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define BLANK_TILE 0


struct Map
{
    int start_x, start_y, max_x, max_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    bool check_valid_tile[20];
    char* file_name;
};

struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int shooting_;
};

namespace SDLGeneralFunc
{
bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
bool isInside(int& x, int& y, SDL_Rect object);
}
#endif // GeneralFunc_H_INCLUDED
