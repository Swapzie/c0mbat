#include "gameObjectHandler.h"

GameObjectHandler::GameObjectHandler(SDL_Surface *objects,
                                     SDL_Surface *projectiles)
{

    m_objects = 0;

    object_sprites = objects;
    projectile_sprites = projectiles;

    number_of_objects = 0;
    number_of_projectiles = 0;
}

void GameObjectHandler::spawn_grenade(int x_pos, int y_pos,
                                    float x_vel, float y_vel)
{ 
    GameProjectile temp(projectile_sprites,x_pos,y_pos,
                        16,16,x_vel,y_vel);

    m_projectiles.push_front(temp);
}

void GameObjectHandler::draw(SDL_Surface *gameScreen)
{
    list<GameProjectile>::iterator i;

    for(i=m_projectiles.begin(); i != m_projectiles.end();++i)
        (*i).draw(gameScreen);
}

void GameObjectHandler::update(unsigned int gameTime)
{

    list<GameProjectile>::iterator i;

    for(i=m_projectiles.begin(); i != m_projectiles.end();++i)
        (*i).update(gameTime);
}


void GameObjectHandler::check_collission(GameMap *map)
{
    list<GameProjectile>::iterator i;

    for(i=m_projectiles.begin(); i != m_projectiles.end();++i)
        (*i).check_collission(map);
}

