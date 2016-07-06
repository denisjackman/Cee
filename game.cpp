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
#include "include/general.h"
#include "include/gamefunction.h"
#include "include/SDLEngine.h"

using namespace std;

//Main code
int main (int argc, char* args[] )
{
    SCREEN_WIDTH        = 640;
    SCREEN_HEIGHT       = 480;
    SCREEN_TITLE        = "Game Project";
    PROGRAM_TIMER       = 2000;
    VERSION             = "V2.02.00";
    NAME_PROGRAM        = "Game Project";
    MEDIAFILE           = "files/texture.png";

  	Print(" -- " + string(NAME_PROGRAM) + " " + string(VERSION) + " (Test) -- ");
	Print(" --- Starting ---");
    if (GameInitialise() == false)
    {
        Print("Game failed to initialise !");
    }
    else
    {
        if (!LoadMedia(MEDIAFILE))
        {
            Print("Game failed to load media ! - " + string(MEDIAFILE ));
        }
        else
        {
            //Main loop flag
            bool gameLoop = true;
            //Event handler
            SDL_Event gameEvent;
            //While application is running
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
				SDL_RenderClear( gRenderer );

				//Render texture to screen
				SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

				//Update screen
				SDL_RenderPresent( gRenderer );
	        }
	     }
	}
	GameTerminate();
	Print(" --- Ending ---");
  	return 0;
}
