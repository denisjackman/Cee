// Standard headers
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>
#include <list>
// Game Library headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
// Custom Headers
#include "include/gamefunction.h"

using namespace std;
// Variables
const int       SCREEN_WIDTH        = 640;
const int       SCREEN_HEIGHT       = 480;
const char      *SCREEN_TITLE       = "Game Project";
const int       PROGRAM_TIMER       = 2000;
const char      *VERSION            = "V2.02.00";
const char      *NAME_PROGRAM       = "Game";
string          MEDIAFILE           = "files/stretch.bmp";
uint32_t        WHITE               = NULL;
SDL_Window*     gWindow             = NULL;
SDL_Surface*    gScreenSurface      = NULL;
SDL_Surface*    gDisplaySurface     = NULL;
SDL_Surface*    gStretchedSurface   = NULL;


// functions
bool GameInitialise()
{
    DebugModeInitialise();
    //Initialization flag
    bool result = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        Print("ERROR:SDL could not initialize! SDL_Error: ");
        result = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            Print("ERROR:Window could not be created! SDL_Error: ");
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
    SDL_FreeSurface( gDisplaySurface );
    gDisplaySurface = NULL;
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    //Quit SDL subsystems
    SDL_Quit();
    DebugModeTerminate();
}

SDL_Surface* loadSurface(string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str() );
    if (loadedSurface == NULL)
    {
        Print("Unable to load image " + path + "! SDL Error: "+ string(SDL_GetError()));
    }
    else
    {
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface=>format, NULL);
        if (optimizedSurface == NULL)
        {
            Print("Unable to optimize image " + path + "! SDL Error: "+ string(SDL_GetError()));
        }
   		SDL_FreeSurface( loadedSurface );
    }
    return optimizedSurface;
}

bool LoadMedia(string path)
{
    bool result = true;
    gDisplaySurface = loadSurface( path);
    if (gDisplaySurface == NULL)
    {
        Print ("ERROR:Unable to load image " + string(SDL_GetError()) + " SDL Error ");
        result = false;
    }
    return result;
}

int main (int argc, char* args[] )
{
  	Print(" -- Game Version 1.0 (Test) -- ");
	Print(" --- Starting ---");
    if (GameInitialise() == false)
    {
        Print("Game failed to initialise !");
    }
    else
    {
        if (!LoadMedia(MEDIAFILE))
        {
            Print("Game failed to load media !");
        }
        else
        {
            //Main loop flag
            bool gameLoop = true;
            //Event handler
            SDL_Event gameEvent;
            //While application is running
	        while( gameLoop )
    	    {
	            //Handle events on queue
		        while( SDL_PollEvent( &gameEvent ) != 0 )
		        {
			        //User requests quit
			        if( gameEvent.type == SDL_QUIT )
			        {
				        gameLoop = false;
			        }
		        }
		        SDL_Rect stretchRect;
		        stretchRect.x = 0;
		        stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
		        stretchRect.h = SCREEN_HEIGHT;
		        SDL_BlitScaled( gStretchedSurface, NULL, gScreenSurface, &stretchRect );
		        //Update the surface
		        SDL_UpdateWindowSurface( gWindow );
	        }
	     }
	}
	GameTerminate();
	Print(" --- Ending ---");
  	return 0;
}


