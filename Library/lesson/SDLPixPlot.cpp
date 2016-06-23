#include <stdlib.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600


int main(void) {
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    bool GameLoop = true;

    SDL_Init(SDL_INIT_VIDEO);
    //
    // SDL_CreateWindowAndRenderer(Width, Height, Window Flags, Target Window, Target Renderer)
    //
    // https://wiki.libsdl.org/SDL_CreateWindowAndRenderer
    //
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    //
    // SDL_SetRenderDrawColor(Target, Red, Green, Blue, Alpha)
    //
    // https://wiki.libsdl.org/SDL_SetRenderDrawColor
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    //
    // SDL_SetRenderDrawColor(Target, Red, Green, Blue, Alpha)
    //
    // https://wiki.libsdl.org/SDL_SetRenderDrawColor
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = 0; i < WINDOW_WIDTH; ++i)
    {
        //
        // SDL_RenderDrawPoint(Target Renderer, X position , Y position)
        //
        // https://wiki.libsdl.org/SDL_RenderDrawPoint
        //
        SDL_RenderDrawPoint(renderer, i, i);
    }
    SDL_RenderPresent(renderer);
    while (GameLoop)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
        {
            GameLoop = false;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}