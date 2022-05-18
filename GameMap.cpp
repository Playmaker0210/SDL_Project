#include "GameMap.h"
#include "GeneralFunc.h"

TileMap::TileMap()
{

}

TileMap::~TileMap()
{

}

/*THAM KHAO TREN LAZYFOO */
void GameMap::LoadMap(std::string path)
{
    int x;
    memset(gMap.check_valid_tile,false,sizeof(gMap.check_valid_tile));
    std::ifstream input(path);
    if (!input)
    {
        return;
    }

    gMap.max_x = 0;
    gMap.max_y = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            input >> gMap.tile[i][j];
            int val = gMap.tile[i][j];
            if (val > 0)
            {
                // Lay vi tri
                if (j > gMap.max_x)
                {
                    gMap.max_x = j;
                }
                if (i > gMap.max_y)
                {
                    gMap.max_y = i;
                }
            }
        }
    }
    input>>x;
    for(int i=0;i<x;i++)
    {
        int t;
        input>>t;
        gMap.check_valid_tile[t]=true;
    }
    // vi tri toi da cua ban do
    gMap.max_x = (gMap.max_x+1)*TILE_SIZE;
    gMap.max_y = (gMap.max_y+1)*TILE_SIZE;

    // vi tri bat dau cua ban do
    gMap.start_x = 0;
    gMap.start_y = 0;

    input.close();
}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    std::string file_name = "";

    for (int i = 0; i < MAX_TILE; i++)
    {
        file_name = "Map/" + std::to_string(i) + ".png" ;

        std::ifstream input(file_name);
        if (!input)
        {
            continue;
        }

        input.close();

        tile_mat[i].LoadImage(file_name, screen);
    }
}

/* THAM KHAO VIDEO HUONG DAN CUA ANH PASS PHAM VE CACH FILL ANH */
// fill cac hinh anh vao o Tile map
void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    // xac dinh xem dang o o thu bao nhieu de fill
    map_x = gMap.start_x/TILE_SIZE;
    x1 = (gMap.start_x%TILE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = gMap.start_y/TILE_SIZE;
    y1 = (gMap.start_y%TILE_SIZE)*-1;
    y2 = x1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = gMap.start_x/TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = gMap.tile[map_y][map_x];
            if (val > 0)
            {
                tile_mat[val].SetupRect(j, i);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}

void GameMap::Format()
{
    for(int i=0;i<7;i++) gMap.tile[i][380]=1;
}
