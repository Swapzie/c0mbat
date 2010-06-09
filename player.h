#ifndef PLAYER_H
#define PLAYER_H

#include "gameMap.h"


enum movement_state{
    Airborne,
    OnGround,
    ClimbingLeftWall,
    ClimbingRightWall
};

struct KeySet
{
    unsigned Up: 1;     // key for Climbing up
    unsigned Down: 1;   // --||--  climbing etc.
    unsigned Left: 1;   // --||--  moving left.
    unsigned Right: 1;  // --||--  moving right
    unsigned Jump: 1;   // --||--  jumping
    unsigned Fire: 1;   // --||--  shooting
    unsigned Reload: 1; // --||--  reloading  
    unsigned Use: 1;    // --||--  using certain map items

    signed Rel_X: 8;    // --||--  Relative position of aim, plus is left
    signed Rel_Y: 8;    // --||--  Rel pos of aim, plus is down. 
};

class Player
{
 public: 
    Player(SDL_Surface *sprite, string name);

    void draw(SDL_Surface *gameSurface, int x_cam, int y_cam);
    void update(unsigned int gameTime);
    void check_collission(GameMap *map);

    void spawn(int x_grid, int y_grid);

    void handle_input(KeySet KS);

    int X() {return (int) x_grid*32 + x_pos;}
    int Y() {return (int) y_grid*32 + y_pos;}


 private:
    SDL_Surface *m_sprite;
    
    SDL_Rect *m_rect;
    SDL_Rect *m_sprite_rect;

    int x_grid, y_grid;
    float x_pos, y_pos;
    float x_vel, y_vel;

    bool isAlive;

    void update_animation(unsigned int gameTime);

    unsigned int lastUpdate;
    unsigned int lastAnimationUpdate;

    string name; 
    movement_state state;
};


#endif
