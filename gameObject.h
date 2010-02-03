#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL/SDL.h>
#include <string>

#include "gameMap.h"


class GameObject
{
 public:
    GameObject(SDL_Surface *sprite, int x, int y, int h, int w);

    void draw(SDL_Surface *gameSurface);
    void update(unsigned int gameTime);

 private:
    SDL_Surface *m_sprite;
    SDL_Rect *m_rect;
    SDL_Rect *m_sprite_rect;

   float x_pos, y_pos;

};

class GameProjectile
{  
 public:
    GameProjectile(SDL_Surface *sprite,
                   int x, int y, int h, int w, float a, float b);    
    
    void draw(SDL_Surface *gameSurface);
    void update(unsigned int gameTime);

    void check_collission(GameMap *map);

    bool check_for_removal(){return expired;}

 private:

    void blow_up(unsigned int atGameTime);
  
    SDL_Surface *m_sprite;
    SDL_Rect *m_rect;
    SDL_Rect *m_sprite_rect;

    int x_grid, y_grid;
    float x_pos, y_pos;
    float x_vel, y_vel;

    unsigned int destroy_at_time;

    bool exploding, expired;
};

#endif

