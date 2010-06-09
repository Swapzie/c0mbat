#include "gameEngine.h"


#define COLORKEY 255, 0, 255
#define BGCOLOR 200, 200, 200

using namespace std;

gameEngine::gameEngine()
{
    done = false;
}


void gameEngine::Load_Content(SDL_Surface *screen)
{
    gameScreen = screen;
    bool debug_feedback = false;
    
    if(debug_feedback)
        cerr << "Loading character sprites...";

    player_sprites = SDL_LoadBMP("./Sprites/Player.bmp");
    if(SDL_SetColorKey(player_sprites, SDL_SRCCOLORKEY | SDL_RLEACCEL,
       SDL_MapRGB(player_sprites->format, COLORKEY)) == -1){
        cout << "Failed to strip Filling Color from char" << endl;
        done = true;
    }
    if(debug_feedback)
        cerr << " done.\nloading object sprites...";

    object_sprites = SDL_LoadBMP("./Sprites/Objects.bmp");
    if(SDL_SetColorKey(object_sprites, SDL_SRCCOLORKEY | SDL_RLEACCEL,
       SDL_MapRGB(object_sprites->format, COLORKEY)) == -1){
        cout << "Failed to strip Filling Color from object" << endl;
        done = true;
    }

    if(debug_feedback)
        cerr << " done.\nloading projectile sprites...";

    projectile_sprites = SDL_LoadBMP("./Sprites/Projectiles.bmp");
    if(SDL_SetColorKey(projectile_sprites, SDL_SRCCOLORKEY | SDL_RLEACCEL,
       SDL_MapRGB(projectile_sprites->format, COLORKEY)) == -1){
        cout << "Failed to strip Filling Color from object" << endl;
        done = true;
    }

    if(debug_feedback)
        cerr << " done.\nloading map sprites...";

    map_border_sprites = SDL_LoadBMP("./Terrain/Debug.bmp");
    if(SDL_SetColorKey(map_border_sprites, SDL_SRCCOLORKEY | SDL_RLEACCEL,
       SDL_MapRGB(map_border_sprites->format, COLORKEY)) == -1){
        cout << "Failed to strip Filling Color from object" << endl;
        done = true;
    }

    if(debug_feedback)
        cerr << " done.\nloading HUD sprites...";

    HUD_sprites = SDL_LoadBMP("./Sprites/HUD_sprites.bmp");
    if(SDL_SetColorKey(HUD_sprites, SDL_SRCCOLORKEY | SDL_RLEACCEL,
       SDL_MapRGB(HUD_sprites->format, COLORKEY)) == -1){
        cout << "Failed to strip Filling Color from object" << endl;
        done = true;
    }
    if(debug_feedback)
        cerr << " done.\n";

    string level = "testlevel";

    if(debug_feedback)
        cerr << "Loading level..." << endl;
    map = new GameMap(string("testlevel"), map_sprites, map_border_sprites, 32);

    if(debug_feedback)
        cerr << "done."<< endl;

    if(debug_feedback)
        map->print(cout);

    SDL_ShowCursor(SDL_DISABLE);
    SDL_WM_GrabInput(SDL_GRAB_OFF);

    mouse_x = mouse_y = 0;


    local_player = new Player(player_sprites, "Pelleh");

    object_handler = new GameObjectHandler(object_sprites, 
                                           projectile_sprites,
                                           player_sprites);

    object_handler -> grab_player_control(local_player);

    

    
    KS.Up = false;
    KS.Left = false;
    KS.Right = false;
    KS.Jump = false;
    KS.Down = false;

    SDL_WarpMouse(304,200);
}

void gameEngine::Load_Map()
{
 //   GE_objects[0] = new GameObject(object_sprites,  5*32,  5*32, 32, 32);
 //   GE_objects[1] = new GameObject(object_sprites,  2*32,  5*32, 32, 32);
 //   GE_objects[2] = new GameObject(object_sprites,  6*32,  1*32, 32, 32);
 //   GE_objects[3] = new GameObject(object_sprites,  16*32+25, 4*32, 32, 32);
//    GE_objects[0] = new GameObject(object_sprites,  17*32,  5*32, 32, 32);


 //   number_of_objects = 1;

}

void gameEngine::Update(unsigned int gameTime)
{

}

void gameEngine::Start_Game()
{


    cerr << "starting game" << endl;

    SDL_FillRect(gameScreen, NULL, SDL_MapRGB(gameScreen->format,200,250,200));

    Draw();
   

    unsigned int gameTime = SDL_GetTicks();
    unsigned int lastUpdate = gameTime;
    unsigned int lastThrow = gameTime;
                        
    int x_cam = 0, y_cam = 0;


    
    while(done == false){


        gameTime = SDL_GetTicks();

        grab_keyboard_events(gameTime);

        /*
        if(gameTime - lastThrow > 1000){ 
            object_handler -> spawn_grenade(100,100,0.4,0.5);
            lastThrow = gameTime;
        }
        */

        object_handler -> update (gameTime - lastUpdate); 
        object_handler -> check_collission(map);


        local_player -> handle_input(KS);
        local_player -> check_collission(map);
        local_player -> update(gameTime - lastUpdate);
        
        Draw(); 


        lastUpdate = gameTime;
        
        SDL_Flip(gameScreen);
    }

    SDL_FreeSurface(player_sprites);
    SDL_FreeSurface(object_sprites);

}

void gameEngine::Draw()
{
    SDL_FillRect(gameScreen,NULL,SDL_MapRGB(gameScreen->format,200,200,250));
    map->draw(gameScreen,local_player->X() - 304, local_player->Y() - 200);

    local_player -> draw(gameScreen, local_player->X()- 304, 
                                     local_player->Y()- 200);

    object_handler->draw(gameScreen);
     
    Draw_HUD();

}


void gameEngine::Draw_HUD()
{
    SDL_Rect *sourceRect = new SDL_Rect();
    SDL_Rect *targetRect = new SDL_Rect();
    targetRect -> h = gameScreen->h - 10*TILESIZE;
    targetRect -> w = gameScreen->w;
    targetRect -> x = 0;
    targetRect -> y = TILESIZE *11;


    SDL_FillRect(gameScreen, targetRect, 
                 SDL_MapRGB(gameScreen->format,100,100,100));


    targetRect -> h = 5;
    targetRect -> w = TILESIZE;
    targetRect -> y = TILESIZE *11;


    sourceRect -> h = 5;
    sourceRect -> w = TILESIZE;
    sourceRect -> x = 0;
    sourceRect -> y = 0;


    for(int i=0; i< 20; i++){
        targetRect -> x = i * TILESIZE;
        SDL_BlitSurface(HUD_sprites,sourceRect,gameScreen,targetRect);
    }
    
    sourceRect -> h = 16;
    sourceRect -> w = 16;
    sourceRect -> x = 32;
    sourceRect -> y = 0;

    targetRect -> h = 16;
    targetRect -> w = 16;
    targetRect -> x = mouse_x - 8;
    targetRect -> y = mouse_y - 8;

    SDL_BlitSurface(HUD_sprites, sourceRect, gameScreen, targetRect);
    
    delete sourceRect;
    delete targetRect; 

}

void gameEngine::grab_keyboard_events(unsigned int gameTime)
{
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_SPACE:
                        KS.Jump = true;
                        break;
                    case SDLK_w:
                        KS.Up = true;
                        break;
                    case SDLK_a:
                        KS.Left = true;
                        break;
                    case SDLK_s:
                        KS.Down = true;
                        break;
                    case SDLK_d:
                        KS.Right = true;
                        break;
                    default: break;

                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        done = true;
                        break;
                    case SDLK_SPACE:
                        KS.Jump = false;
                        break;
                    case SDLK_w:
                        KS.Up = false;
                        break;
                    case SDLK_a:
                        KS.Left = false;
                        break;

                    case SDLK_s:
                        KS.Down = false;
                        break;
                    case SDLK_d:
                        KS.Right = false;
                        break;


                    case SDLK_o:
                        local_player->spawn(2,2);
                        break;

                    case SDLK_p:
                        object_handler -> spawn_grenade();
                        break; 
                    default: break;
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
                switch(SDL_GetMouseState(&mouse_x, &mouse_y)){
                    case SDL_BUTTON(SDL_BUTTON_LEFT):
                        object_handler -> spawn_grenade();
                        break;

                    default: break;
                }
            case SDL_MOUSEMOTION:
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                object_handler -> set_mouse_position(mouse_x, mouse_y);
            break;
            case SDL_QUIT: 
                done = true;
            break;
                default:
            break;
        }
    }
}

