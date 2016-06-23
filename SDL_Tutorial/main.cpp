// Standard headers
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>
#include <list>
#include <string>

// Game Library headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Custom Headers
#include "../include/general.h"
#include "../include/SDLEngine.h"

using namespace std;

//Main code
int main (int argc, char* args[] )
{
    SCREEN_WIDTH        = 640;
    SCREEN_HEIGHT       = 480;
    SCREEN_TITLE        = "SDL Tutorial";
    PROGRAM_TIMER       = 2000;
    VERSION             = "V1.00.00";
    NAME_PROGRAM        = "SDL Tutorial";
    MEDIAFILE           = "files/texture.png";
    srand(time(0));

    int x = 0;
    int y = 0;
    int red = 0;
    int green = 0;
    int blue = 0;

  	Print(" --- " + string(NAME_PROGRAM) + " " + string(VERSION) + " (Test) --- ");
    Print(" --- Starting ---");
    if (GameInitialise() == false)
    {
        Print(string(NAME_PROGRAM) + " " + string(VERSION) +" failed to initialise !");
    }
    //Main loop flag
    bool gameLoop = true;
    //Event handler
    SDL_Event gameEvent;
    //While application is running
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
	SDL_RenderClear( gRenderer );
	while ( gameLoop )
    {
	    //Handle events on queue
		while ( SDL_PollEvent(&gameEvent ) != 0 )
		{
	        //User requests quit
			if ( gameEvent.type == SDL_QUIT)
			{
		        gameLoop = false;
			}
		}

		//Clear screen
		x  = rand() % SCREEN_WIDTH + 1;
		y  = rand() % SCREEN_HEIGHT +1;
		red = rand() % 255;
		green = rand() % 255;
		blue = rand() % 255;

        PlotPixel( x, y, red, green, blue);

		//Update screen
		SDL_RenderPresent( gRenderer );
	}
    GameTerminate();
    Print(" --- Ending   ---");
}