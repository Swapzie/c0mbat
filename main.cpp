#include <math.h>
#include <iostream>
#include <SDL/SDL.h>

#include "simConst.h"
#include "gameEngine.h"

using namespace std;

void print_version();
void print_usage();

int main (int argc, char *argv[]) 
{
    Uint32 fbflags = 0;
    Uint32 surfaceflags = 0;

    SDL_Surface *s_screen;
    gameEngine *GE;    

    //Parse command line arguments
    for(int i=1; i< argc; i++){
        if((string)argv[i] == "--help"){
            print_usage();
            return 0;
        }
        else if((string)argv[i] == "--version"){
            print_version();
            return 0;
        }
        else if((string)argv[i] == "--fullscreen"){
            fbflags |= SDL_FULLSCREEN;
            cout << "fullscreen set as true" << endl;
        }
        else{
            cout << "Unknown option: " << argv[i] << endl;
            return 1;
        }
    }

    //Load back-end
    GE = new gameEngine();

    if(SDL_Init(SDL_INIT_VIDEO) !=0 ){
        cerr << "Error: unable to initialize video: ";
        cerr << SDL_GetError() << endl;
        return 1;
    }else cout << "Video up" << endl;

    if(SDL_Init(SDL_INIT_AUDIO) != 0){
        cerr << "Warning: unable to initialize audio: ";
        //cerr << SDL_GetError() << endl;
    }else cout << "Audio up" << endl;

//   if(Mix_OpenAudio(11025, AUDIO_S16, 2, 512) < 0){
//      cerr << "Warning: audio could not be set up for";
//     cerr << "11025 Hz 16-bit stereo.\nReason: \n" << SDL_GetError();
//   }

    if(SDL_GetVideoInfo() -> hw_available){
        cout << "Using hardware surface" << endl;
        surfaceflags |= (SDL_HWSURFACE);
    }
    else{
        cout << "No Hardware surface available, "
             << "using software surface" << endl;
        surfaceflags |= (SDL_SWSURFACE);
    }



    s_screen=SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_DOUBLEBUF|fbflags|surfaceflags);
    if(s_screen == NULL){
        cerr << "Error: unable to set video mode: " << SDL_GetError();
        return 1;
    } else cout << "Video mode seems fine" << endl; 

    SDL_WM_SetCaption("c0mbat", "c0mbat");

    

    GE -> Load_Content(s_screen);

    GE -> Load_Map();
    GE -> Start_Game();

    SDL_Quit();

    cout << "SDL_Quit()" << endl;
    return 0;
}

void print_version()
{
    cout << "This is [tehProject] pre-Beta" << endl;
}
void print_usage()
{
    cout << "tehProject [OPTIONS]:  \n\
                                    \n\
            Options. \n\
            --fullscreen\tstarts game in full screen mode\n\
            --version\tprints current version\n\
            --help\tprint this message and exit\n\n";
}






