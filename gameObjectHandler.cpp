#include "gameObjectHandler.h"

GameObjectHandler::GameObjectHandler(SDL_Surface *objects,
                                     SDL_Surface *projectiles,
                                     SDL_Surface *players)
{

    m_objects = 0;

    object_sprites = objects;
    projectile_sprites = projectiles;
    player_sprites = players;

    number_of_objects = 0;
    number_of_projectiles = 0;
    number_of_players = 0;
}

void GameObjectHandler::spawn_grenade()
{ 
    double speedX = (double)(mouseX - 304) / 600;
    double speedY = (double)(mouseY - 200) / 200;

    GameProjectile temp(projectile_sprites,
                        m_local_player->X(),
                        m_local_player->Y(),
                        16,16,speedX,speedY);

    m_projectiles.push_front(temp);
}

void GameObjectHandler::draw(SDL_Surface *gameScreen)
{
    cameraX = m_local_player -> X() - 304;
    cameraY = m_local_player -> Y() - 200;

    list<GameProjectile>::iterator i;

    for(i=m_projectiles.begin(); i != m_projectiles.end();++i)
        (*i).draw(gameScreen, cameraX, cameraY);
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

