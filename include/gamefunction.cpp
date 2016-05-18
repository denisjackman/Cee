#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

int Dice(int rolls = 1, int sides = 6)
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

bool GameInit()
{
    //Initialization flag
    bool result = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        result = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            result = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return result;
}