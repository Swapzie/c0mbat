#include "player.h"

Player::Player(SDL_Surface *sprite, string name)
{
    m_sprite = sprite;
    name = name;

    isAlive = false;

    m_rect = new SDL_Rect;
    m_rect -> x = 0;
    m_rect -> y = 0;
    m_rect -> h = 64;
    m_rect -> w = 32;

    x_pos = 0;
    y_pos = 0;

    x_grid = 4;
    y_grid = 0;

    state = Airborne;

}

void Player::draw(SDL_Surface *gameSurface, int x_cam, int y_cam)
{
    m_rect -> x = x_grid*32 + x_pos - x_cam;
    m_rect -> y = y_grid*32 + y_pos - y_cam;
    SDL_BlitSurface(m_sprite, NULL, gameSurface, m_rect);

}

void Player::update(unsigned int gameTime)
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

    if(state == Airborne)
        y_vel += 0.0015 * gameTime;

}

void Player::check_collission(GameMap *map)
{

    if (x_grid > 0 && x_grid < map->width()-1){
        if(y_grid >= 0 && y_grid < map -> height()-2){

            switch(state){
                case OnGround:
                    if (x_vel > 0){
                        if(map->tile_at(x_grid +1, y_grid) > 0 ||
                           map->tile_at(x_grid +1, y_grid+1) > 0){
                            x_vel = 0;
                            x_pos = 0;
                        }
                    }
                    else if(x_vel < 0){

                        if((map -> tile_at(x_grid -1, y_grid) > 0  ||
                            map -> tile_at(x_grid -1, y_grid+1) > 0)

                            && x_pos < 10){
                            x_vel = 0;
                            x_pos = 0;
                        }
                    }
                    if (map -> tile_at(x_grid, y_grid+2)==0)
                        state = Airborne;

                break;
                case Airborne:
                    if(y_vel < 0){
                        if(map -> tile_at(x_grid, y_grid) > 0){
                            //|| x_pos > 5 && map -> tile_at(x_grid +1, y_grid -1) > 0){
                            y_pos = 0;
                            y_grid++;
                            y_vel = 0;

                        }
                    }
                    if (x_vel > 0){
                        if(map->tile_at(x_grid +1, y_grid+1) > 0){
                            x_vel = 0;
                            x_pos = 0;
                            state = ClimbingRightWall;
                        }
                        else if(map->tile_at(x_grid +1, y_grid) > 0){
                            x_vel = 0;
                            x_pos = 0;
                        }
                    }
                    else if(x_vel < 0){

                        if(map -> tile_at(x_grid -1, y_grid+1) > 0 
                                                    && x_pos < 10){
                            x_vel = 0;
                            x_pos = 0;
                            state = ClimbingLeftWall;
                        }
                        else if(map -> tile_at(x_grid -1, y_grid) > 0
                                                    && x_pos < 10) {
                            x_vel = 0;
                            x_pos = 0;
                        }
                    }
                    if(y_vel > 0){
                        if(map -> tile_at(x_grid, y_grid + 2) > 0 || 
                           (x_pos > 0 && map -> tile_at
                           (x_grid+1, y_grid + 2) > 0)){
                            y_vel = 0;
                            y_pos = 0;
                            state = OnGround;
                        }
                    }
                break;
                case ClimbingRightWall:
                    if(y_vel > 0){
                        if (map -> tile_at(x_grid, y_grid+2)>0){
                            y_vel = 0;
                            y_pos = 0;
                            state = OnGround;
                        }
                    }
                    else if(y_vel < 0){
                        if(map -> tile_at(x_grid, y_grid) > 0){
                            y_pos = 0;
                            y_grid++;
                            y_vel = 0;
                        }
                    }
                    if(map -> tile_at(x_grid+1, y_grid+2) == 0 &&
                       map -> tile_at(x_grid+1, y_grid+1) == 0){
                        state = Airborne;
                    }

                break;
                case ClimbingLeftWall:
                    if(y_vel > 0){
                        if (map -> tile_at(x_grid, y_grid+2)>0){
                            y_vel = 0;
                            y_pos = 0;
                            state = OnGround;
                        }
                    }
                    else if(y_vel < 0){
                        if(map -> tile_at(x_grid, y_grid) > 0){
                            y_pos = 0;
                            y_grid++;
                            y_vel = 0;
                        }
                    }
                    if(map -> tile_at(x_grid-1, y_grid+2) == 0 &&
                       map -> tile_at(x_grid-1, y_grid+1) == 0){
                        state = Airborne;
                    }
                break;
            }

        }
    }

}

void Player::handle_input(KeySet KS)
{

    switch(state){
        case OnGround:
            if(KS.Jump){
                state = Airborne;
                y_vel = -0.7;
            }
            if (KS.Left && !KS.Right)
                x_vel = -0.4;
            if (KS.Right && !KS.Left)
                x_vel = 0.4;
            if ((KS.Right && KS.Left) ||
               (!KS.Right && !KS.Left))
                x_vel *= 0.8; 
        break;
        case Airborne:
        
            if (KS.Left && !KS.Right)
                x_vel = -0.3;
            if (KS.Right && !KS.Left)
                x_vel = 0.3;
            if ((KS.Right && KS.Left) ||
               (!KS.Right && !KS.Left))
                x_vel *= 0.99; 
            break;

        case ClimbingRightWall:
            if (KS.Jump){
                y_vel = -0.6;
                x_vel = -0.5;
                state = Airborne;
            }
            else {
                if (KS.Left){
                    state = Airborne;
                    x_vel = -0.1;
                }
                if (KS.Up && !KS.Down){
                    y_vel = -0.1;
                }
                if (KS.Down){
                    y_vel = 0.4;
                }
                if ((KS.Up && KS.Down) ||
                   (!KS.Up && !KS.Down)){
                    y_vel *= 0.8; 
                    if(y_vel < 0.015)
                        y_vel = 0.015;
                }
            }
            break;

        case ClimbingLeftWall:
        x_vel = 0;
            if (KS.Jump){
                y_vel = -0.6;
                x_vel = 0.5;
                state = Airborne;
            }
            else {
                if(KS.Right){
                    state = Airborne;
                    x_vel = 0.1;
                }   
                if (KS.Up && !KS.Down){
                    y_vel = -0.1;
                }
                if (KS.Down && !KS.Up){
                    y_vel = 0.4;
                }
                if ((KS.Up && KS.Down) ||
                   (!KS.Up && !KS.Down)){
                    y_vel *= 0.8; 
                    if(y_vel < 0.015)
                        y_vel = 0.015;
                }
            }
        break;
    }
}

void Player::spawn(int grid_x, int grid_y)
{
   
    if(!isAlive){
        state = Airborne;
        isAlive = true;
        x_grid = grid_x;
        y_grid = grid_y;

    }
}
