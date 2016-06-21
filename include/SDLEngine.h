#ifndef SDLENGINE_H
#define SDLENGINE_H

using namespace std;



// Function Headers
bool GameInitialise();
void GameTerminate();
SDL_Surface* loadSurface(string path);
SDL_Texture* loadTexture( string path );
bool LoadMedia(string path);

#endif