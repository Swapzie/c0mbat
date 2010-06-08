#include "gameObject.h"

using namespace std;

GameObject::GameObject(SDL_Surface *sprite, int x, int y, int h, int w)
{
    m_sprite = sprite;
    m_rect = new SDL_Rect;
    m_rect->x = 0;
    m_rect->y = 0;
    m_rect->h = h;
    m_rect->w = w;

    x_pos = x;
    y_pos = y;

    m_sprite_rect = new SDL_Rect;
    m_sprite_rect->x = 0;
    m_sprite_rect->y = 0;
    m_sprite_rect->h = 32;
    m_sprite_rect->w = 32;
}

void GameObject::draw(SDL_Surface *gameSurface, int x_cam, int y_cam)
{
    m_rect -> x = x_pos - x_cam;
    m_rect -> y = y_pos - y_cam;
    SDL_BlitSurface(m_sprite, NULL, gameSurface, m_rect);
}

void GameObject::update(unsigned int gameTime)
{

}

GameProjectile::GameProjectile(SDL_Surface *sprite, int x, int y, int h, int w, 
                               float vel_x, float vel_y)
{
    m_sprite = sprite;
    m_rect = new SDL_Rect;
    m_rect->x = 0;
    m_rect->y = 0;
    m_rect->h = h;
    m_rect->w = w;

    x_grid = 0;
    y_grid = 0;

    x_pos = x;
    y_pos = y;

    x_vel = vel_x;
    y_vel = vel_y;


    m_sprite_rect = new SDL_Rect;
    m_sprite_rect->x = 0;
    m_sprite_rect->y = 0;
    m_sprite_rect->h = 32;
    m_sprite_rect->w = 32;

    exploding = false;
    expired = false;


    while(x_pos > 32){
        x_pos -= 32;
        ++ x_grid;
    }
    while(x_pos < 0){
        x_pos += 32;
        --x_grid;
    }
    
    while(y_pos > 32){
        y_pos -= 32;
        ++ y_grid;
    }
    while(y_pos < 0){
        y_pos += 32;
        -- y_grid;
    }
}

void GameProjectile::draw(SDL_Surface *gameSurface, int x_cam, int y_cam)
{
    m_rect -> x = x_grid*32 + x_pos - x_cam;
    m_rect -> y = y_grid*32 + y_pos - y_cam;
    SDL_BlitSurface(m_sprite, NULL, gameSurface, m_rect);
}

void GameProjectile::check_collission(GameMap *map)
{
    if (x_grid > 0 && x_grid < map->width()-1){
        if(y_grid > 0 && y_grid < map -> height()){
            if(x_vel > 0){
                if(map->tile_at(x_grid +1, y_grid) > 0 
                   && x_pos > 15){
                    x_vel = -x_vel;
                    x_pos = 15;
                }
            }
            if (x_vel < 0){
                if(map -> tile_at(x_grid, y_grid) > 0){
                    x_vel = -0.4 * x_vel;
                    x_pos = 0;
                    x_grid ++;
                }
            }
            if (y_vel < 0){
                if(map -> tile_at(x_grid, y_grid) > 0){
                    y_grid++;
                    y_vel = 0;
                    y_pos = 0;
                }
            }

            if(y_vel > 0){
                if(map -> tile_at(x_grid, y_grid + 1) > 0
                    && y_pos > 15){
                    y_vel = - 0.40 * y_vel;
                    x_vel *= 0.8;
                    y_pos = 16;
                    if(y_vel*y_vel < 0.00005){
                        y_vel = 0;
                    }
                }
            } 

        }
    }
}

void GameProjectile::update(unsigned int gameTime)
{

    x_pos += x_vel * gameTime;
    y_pos += y_vel * gameTime;

    if(x_pos > 32){
        x_pos -= 32;
        ++ x_grid;
    }
    else if(x_pos < 0){
        x_pos += 32;
        --x_grid;
    }
    
    if(y_pos > 32){
        y_pos -= 32;
        ++ y_grid;
    }
    else if(y_pos < 0){
        y_pos += 32;
        -- y_grid;
    }


    y_vel += 0.0015 * gameTime;

    //if(destroy_at_time < gameTime)
        //expired = true;
}

void GameProjectile::initiate()
{
    while(x_pos > 32){
        x_pos -= 32;
        ++ x_grid;
    }
    while(x_pos < 0){
        x_pos += 32;
        --x_grid;
    }
    
    while(y_pos > 32){
        y_pos -= 32;
        ++ y_grid;
    }
    while(y_pos < 0){
        y_pos += 32;
        -- y_grid;
    }

}
void GameProjectile::blow_up(unsigned int atGameTime)
{
    exploding = true;
    destroy_at_time = atGameTime;
}

