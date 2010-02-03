#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include <list>

#include "gameObject.h"

using namespace std;

class GameObjectHandler
{
 public:
    GameObjectHandler(SDL_Surface *objects, SDL_Surface *projectiles);

    void spawn_grenade(int x_pos = 200, int y_pos = 200,
                       float x_vel = 0, float y_vel = 0);
    void update(unsigned int gameTime);
    void check_collission(GameMap *map);

    void draw(SDL_Surface *gameScreen);

 private:
    GameObject *m_objects;

    int number_of_objects;
    int number_of_projectiles;

    list<GameProjectile> m_projectiles;

    SDL_Surface *object_sprites;
    SDL_Surface *projectile_sprites;
};

#endif

