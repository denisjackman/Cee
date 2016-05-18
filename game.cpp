#include <SDL2/SDL.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdint>
#include "include/gamefunction.h"

using namespace std;

const int   SCREEN_WIDTH    = 640;
const int   SCREEN_HEIGHT   = 480;
const char  *SCREEN_TITLE   = "Game Project";
const int   PROGRAM_TIMER   = 2000;
const char  *VERSION        = "V2.01.00";
const char  *NAME_PROGRAM   = "Game";
uint32_t WHITE = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
/* This not needed yet
//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
*/
bool GameInit()
{
    //Initialization flag
    bool result = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        result = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            cout << "Window could not be created! SDL_Error: " <<  SDL_GetError() << endl;
            result = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
            WHITE = SDL_MapRGB( gScreenSurface->format, 0xFF, 0xFF, 0xFF );
        }
    }
    return result;
}

void GameTerminate()
{
    //Deallocate surface
    //SDL_FreeSurface( gHelloWorld );
    //gHelloWorld = NULL;
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    //Quit SDL subsystems
    SDL_Quit();
}

/*
	This is an ongoing project 
*/
int main (int argc, char* args[] )
{
    if (GameInit())
    {
       //Fill the surface white
       SDL_FillRect( gScreenSurface, NULL, WHITE );
       //Update the surface
       SDL_UpdateWindowSurface( gWindow );
       //Wait two seconds
       SDL_Delay( PROGRAM_TIMER );
    }
    else
    {
        cout << "Game failed to initialise !" << endl;
    }
  	cout << " -- Game Version 1.0 (Test) -- " << endl;
	cout << " --- Starting ---" << endl;
	cout << " One Dice roll only Vasily -- " << Dice() << endl;
	cout << " Distance to target Vasily -- " << Distance(1,0,10,0) << endl;
	cout << " Got a Colour >" << WHITE << "< " << endl;
	cout << " --- Ending ---" << endl;

	GameTerminate();
  	return 0;
}