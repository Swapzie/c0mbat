#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL/SDL.h>
#include <iostream>
#include <math.h>
#include <stack>

#include "simConst.h"
#include "gameMap.h"
#include "gameObject.h"
#include "gameObjectHandler.h"
#include "player.h"

using namespace std;


class gameEngine
{
 public:
    gameEngine();
    void set_done(){done = true;}
    
    void Load_Content(SDL_Surface *screen);
    void Load_Map();
    void Start_Game();
    void Update(unsigned int gameTime);
    void Draw();

    void test();

 private:
    int mouse_x, mouse_y;
    void add_game_object(GameObject obj);
    
    void blit_game_objects(SDL_Surface *screen);
    void Draw_HUD();

    void grab_keyboard_events(unsigned int gameTime); 
    bool done;

    SDL_Surface *gameScreen;

    SDL_Surface *player_sprites;
    SDL_Surface *object_sprites;
    SDL_Surface *projectile_sprites;

    SDL_Surface *map_sprites;
    SDL_Surface *map_border_sprites;

    SDL_Surface *HUD_sprites;

    GameMap* map; 

    GameObject *GE_objects[100];
    GameObject *test_object;
    int number_of_objects;

    GameObjectHandler *object_handler;

    Player *local_player;
    KeySet KS;
};

#endif
