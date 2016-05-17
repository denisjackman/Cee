#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char *SCREEN_TITLE = "Game Project Template";
const int PROGRAM_TIMER = 2000;
const char *VERSION = "V1.00.00";
const char *NAME_PROGRAM = "Functions";

int Dice(int rolls, int sides)
{
	int result = 0;
	srand(time(NULL));
	for ( int loop =0; loop < rolls; loop = loop + 1)
	{
        	result += rand() % sides + 1;
	}
	return result;
}

int Distance(double oX0, double oY0, double tX1, double tY1)
{
    double result = 0;
    result = sqrt((tX1 - oX0)*(tX1 - oX0) + (tY1 - oY0)*(tY1 - oY0));
    return int(result);
}

int main( int argc, char* args[] )
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
/*	cout << "here " << endl;
	try
	{
        Uint32 WHITE = SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF);
	}
	catch ( exception& e)
	{
        cout << e.what() << endl;
	}
	cout << "here too" << endl;
*/
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
	return 0;
}
