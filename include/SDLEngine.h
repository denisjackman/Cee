#ifndef SDLENGINE_H
#define SDLENGINE_H

using namespace std;

// Variables
extern int             SCREEN_WIDTH;
extern int             SCREEN_HEIGHT;
extern char            *SCREEN_TITLE;
extern int             PROGRAM_TIMER;
extern char            *VERSION;
extern char            *NAME_PROGRAM;
extern string          MEDIAFILE;
extern SDL_Window*     gWindow;
extern SDL_Surface*    gScreenSurface;
extern SDL_Surface*    gDisplaySurface;
extern SDL_Surface*    gStretchedSurface;
extern SDL_Renderer*   gRenderer;
extern SDL_Texture*    gTexture;

// Function Headers
bool GameInitialise();
void GameTerminate();
SDL_Surface* loadSurface(string path);
SDL_Texture* loadTexture( string path );
bool LoadMedia(string path);
void PlotPixel( int x, int y, int red, int green, int blue);

#endif