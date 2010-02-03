#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <fstream>
#include <iostream>
#include <SDL/SDL.h>
#include <sstream>

using namespace std;

class GameMap
{
 public:
    GameMap(string fileName, SDL_Surface *map_sprites,
            SDL_Surface *map_border_sprites, int tileSize);
    ~GameMap();
    
    void draw(SDL_Surface *screen, int x_cam, int y_cam);

    void read_from_file(string fileName);
    char tile_at(int x, int y);
    void print(ostream &out);
    void print_int(ostream &out);

    int height(){return m_height;}
    int width(){return m_width;}

 private:
    
    void parse_borders();
    int find_tile(int testX, int testY);
    
    int m_tileSize;
    SDL_Surface *m_sprites;
    SDL_Surface *m_border_sprites;

    int m_width, m_height;
    char** m_map_matrix;
    char** m_map_borders;


};

#endif

