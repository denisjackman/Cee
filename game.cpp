#include <SDL2/SDL.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <stdint.h>
#include "include/gamefunction.h"

using namespace std;

const int   SCREEN_WIDTH    = 640;
const int   SCREEN_HEIGHT   = 480;
const char  *SCREEN_TITLE   = "Game Project Template";
const int   PROGRAM_TIMER   = 2000;
const char  *VERSION        = "V1.00.00";
const char  *NAME_PROGRAM   = "Functions";

/*
	This is an ongoing project 
*/
int main (int argc, char* args[] )
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
    uint32_t WHITE = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
	}
	else
	{
		window = SDL_CreateWindow( SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			cout << "Window could not be created! SDL_Error:" << SDL_GetError() << endl;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface( window );
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format , 0x00, 0x00, 0x00) );
			SDL_UpdateWindowSurface( window );
			SDL_Delay( PROGRAM_TIMER );
		}
	}
	SDL_DestroyWindow( window );
	SDL_Quit();
  	cout << " -- Game Version 1.0 (Test) -- " << endl;
	cout << " --- Starting ---" << endl;
	cout << " One Dice roll only Vasily -- " << Dice() << endl;
	cout << " Distance to target Vasily -- " << Distance(1,0,10,0) << endl;
	cout << " --- Ending ---" << endl;
  	return 0;
}
