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

bool windowInit();
void Windowfree();
void ghandleEvent( SDL_Event& e );
void lhandleEvent( SDL_Event& e );


SDL_Window*     lWindow             = NULL;
SDL_Surface*    lScreenSurface      = NULL;
SDL_Renderer*   lRenderer           = NULL;
SDL_Texture*    lTexture            = NULL;
int             gWindowID;
int             lWindowID;

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
        windowInit();
        gWindowID = SDL_GetWindowID( gWindow );
		lWindowID = SDL_GetWindowID( lWindow );
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
                    ghandleEvent(gameEvent);
				    if( gameEvent.type == SDL_KEYDOWN )
				    {
					    switch( gameEvent.key.keysym.sym )
					    {
						    case SDLK_1:
						        SDL_ShowWindow( gWindow );
	                            //Move window forward
	                            SDL_RaiseWindow( gWindow );
						        break;

						    case SDLK_2:
						        SDL_ShowWindow( gWindow );
	                            //Move window forward
	                            SDL_RaiseWindow( gWindow );
						        break;
							
						    case SDLK_3:
						        SDL_ShowWindow( gWindow );
	                            //Move window forward
	                            SDL_RaiseWindow( gWindow );
						        break;
					    }
					}
                    lhandleEvent(gameEvent);

				    if( gameEvent.type == SDL_KEYDOWN )
				    {
					    switch( gameEvent.key.keysym.sym )
					    {
						    case SDLK_1:
						        SDL_ShowWindow( lWindow );
	                            //Move window forward
	                            SDL_RaiseWindow( lWindow );
						        break;

						    case SDLK_2:
						        SDL_ShowWindow( lWindow );
	                            //Move window forward
	                            SDL_RaiseWindow( lWindow );
						        break;
							
						    case SDLK_3:
						        SDL_ShowWindow( lWindow );
	                            //Move window forward
	                            SDL_RaiseWindow( lWindow );
						        break;
					    }
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
	Windowfree();
	GameTerminate();
	Print(" --- Ending ---");
  	return 0;
}

bool windowInit()
{
	//Create window
	lWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( lWindow != NULL )
	{

		//Create renderer for window
		lRenderer = SDL_CreateRenderer( lWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if( lRenderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			SDL_DestroyWindow( lWindow );
			lWindow = NULL;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor( lRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

		}
	}
	else
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	return lWindow != NULL && lRenderer != NULL;
}
void Windowfree()
{
	if( lWindow != NULL )
	{
		SDL_DestroyWindow( lWindow );
	}
}

void ghandleEvent( SDL_Event& e )
{
	//If an event was detected for this window
	if( e.type == SDL_WINDOWEVENT && e.window.windowID == gWindowID )
	{
		//Caption update flag
		bool updateCaption = false;

		switch( e.window.event )
		{

			//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			    SDL_RenderPresent( gRenderer );
			    break;

			//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
			    SDL_RenderPresent( gRenderer );
			    break;
			
			//Hide on close
			case SDL_WINDOWEVENT_CLOSE:
			    SDL_HideWindow( gWindow );
			    break;
		}
	}
}

void lhandleEvent( SDL_Event& e )
{
	//If an event was detected for this window
	if( e.type == SDL_WINDOWEVENT && e.window.windowID == lWindowID )
	{
		//Caption update flag
		bool updateCaption = false;

		switch( e.window.event )
		{

			//Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			    SDL_RenderPresent( lRenderer );
			    break;

			//Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
			    SDL_RenderPresent( lRenderer );
			    break;

			//Hide on close
			case SDL_WINDOWEVENT_CLOSE:
			    SDL_HideWindow( lWindow );
			    break;
		}
	}
}