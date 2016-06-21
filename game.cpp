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

using namespace std;

// Custom Headers
#include "include/gamefunction.h"
#include "include/SDLEngine.h"


//Main code
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
            int counter = 0;
            //Event handler
            SDL_Event gameEvent;
            //While application is running
	        while ( gameLoop )
    	    {
	            //Handle events on queue
		        while ( SDL_PollEvent(&gameEvent ) != 0 )
		        {
		            counter++;
			        //User requests quit
			        if ( gameEvent.type == SDL_QUIT)
			        {
				        gameLoop = false;
			        }
			        if ( counter > 3000)
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



