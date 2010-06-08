#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include <list>

#include "gameObject.h"
#include "player.h"

using namespace std;

class GameObjectHandler
{
 public:
    GameObjectHandler(SDL_Surface *objects, 
                      SDL_Surface *projectiles, 
                      SDL_Surface *players);

    void spawn_grenade();
    void update(unsigned int gameTime);
    void check_collission(GameMap *map);

    void grab_player_control(Player *player) {m_local_player = player;}
    void set_mouse_position(int mX, int mY){mouseX = mX; mouseY = mY;}

    void draw(SDL_Surface *gameScreen);

 private:
    GameObject *m_objects;
    
    int cameraX, cameraY;
    int mouseX, mouseY;
    
    int number_of_objects;
    int number_of_projectiles;
    int number_of_players;

    Player *m_local_player;
    
    list<Player> m_players;
    list<GameProjectile> m_projectiles;

    SDL_Surface *object_sprites;
    SDL_Surface *projectile_sprites;
    SDL_Surface *player_sprites;
};

#endif

