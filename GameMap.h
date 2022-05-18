// lop ban do
#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include "GeneralFunc.h"
#include "BaseObj.h"

#define MAX_TILE 20

class TileMap: public baseObject
{
public:
    TileMap();
    ~TileMap();

};
class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}
    void LoadMap(std::string path);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map get_map()
    {
        return gMap;
    };
    void SetMap(Map& data)
    {
        gMap= data;
    }
    void Format();
private:
    Map gMap;
    TileMap tile_mat[MAX_TILE];
};
#endif // GAMEMAP_H_INCLUDED
