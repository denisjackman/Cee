#ifndef SDLENGINE_H
#define SDLENGINE_H

using namespace std;

// Variables
const int       SCREEN_WIDTH        = 640;
const int       SCREEN_HEIGHT       = 480;
const char      *SCREEN_TITLE       = "Game Project";
const int       PROGRAM_TIMER       = 2000;
const char      *VERSION            = "V2.02.00";
const char      *NAME_PROGRAM       = "Game";
string          MEDIAFILE           = "files/texture.png";
uint32_t        WHITE               = NULL;
SDL_Window*     gWindow             = NULL;
SDL_Surface*    gScreenSurface      = NULL;
SDL_Surface*    gDisplaySurface     = NULL;
SDL_Surface*    gStretchedSurface   = NULL;
SDL_Renderer*   gRenderer           = NULL;
SDL_Texture*    gTexture            = NULL;

// Function Headers
bool GameInitialise();
void GameTerminate();
SDL_Surface* loadSurface(string path);
SDL_Texture* loadTexture( string path );
bool LoadMedia(string path);

#endif