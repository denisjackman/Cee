#include "SDL2/SDL.h"


#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE    32
#define SCREEN_TITLE  "SDL Move"
int main(int argc, char* argv[])
{
	SDL_Surface     *temp;
	SDL_Window*     window = NULL;
	SDL_Renderer*   renderer = NULL;
	SDL_Texture*    sprite = NULL;
	SDL_Texture*    grass = NULL;
	SDL_Texture*    screen = NULL;
	SDL_Rect        rcSprite, rcGrass, rcScreen;
	SDL_Event       event;

	const unsigned char   *keystate;
	int                   colorkey;
	int                   gameover;

	SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow( SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	/* load grass */
	temp  = SDL_LoadBMP("grass.bmp");
	grass = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	/* load sprite */
	temp   = SDL_LoadBMP("sprite.bmp");
	/* now we set the background to transparent ff00ff */
	SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0, 0xFF ) );
	sprite = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	/* set sprite position */
	rcSprite.x = 0;
	rcSprite.y = 0;
	rcSprite.w = SPRITE_SIZE;
	rcSprite.h = SPRITE_SIZE;

    rcScreen.x = SCREEN_WIDTH / 2 - SPRITE_SIZE / 2;
    rcScreen.y = SCREEN_HEIGHT / 2 - SPRITE_SIZE / 2;
    rcScreen.w = SPRITE_SIZE;
	rcScreen.h = SPRITE_SIZE;

	gameover = 0;

	/* message pump */
	while (!gameover)
	{
		//Clear screen
		SDL_RenderClear( renderer );
		/* look for an event */
		if (SDL_PollEvent(&event)) {
			/* an event was found */
			switch (event.type) {
				/* close button clicked */
				case SDL_QUIT:
					gameover = 1;
					break;

				/* handle the keyboard */
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
						case SDLK_q:
							gameover = 1;
							break;
					}
					break;
			}
		}

		/* handle sprite movement */
		/*
		keystate = SDL_GetKeyboardState(NULL);

		if (keystate[SDL_SCANCODE_LEFT] ) {
			rcSprite.x -= 2;
		}
		if (keystate[SDL_SCANCODE_RIGHT] ) {
			rcSprite.x += 2;
		}
		if (keystate[SDL_SCANCODE_UP] ) {
			rcSprite.y -= 2;
		}
		if (keystate[SDL_SCANCODE_DOWN] ) {
			rcSprite.y += 2;
		}
        */
		/* collide with edges of screen
		if ( rcSprite.x < 0 ) {
			rcSprite.x = 0;
		}
		else if ( rcSprite.x > SCREEN_WIDTH-SPRITE_SIZE ) {
			rcSprite.x = SCREEN_WIDTH-SPRITE_SIZE;
		}
		if ( rcSprite.y < 0 ) {
			rcSprite.y = 0;
		}
		else if ( rcSprite.y > SCREEN_HEIGHT-SPRITE_SIZE ) {
			rcSprite.y = SCREEN_HEIGHT-SPRITE_SIZE;
		}
		*/
        rcScreen.x = rcSprite.x;
        rcScreen.y = rcSprite.y;
		/* draw the grass */
		for (int x = 0; x < SCREEN_WIDTH/SPRITE_SIZE; x++) {
			for (int y = 0; y < SCREEN_HEIGHT/SPRITE_SIZE; y++) {
				rcGrass.x = x * SPRITE_SIZE;
				rcGrass.y = y * SPRITE_SIZE;
				rcScreen.x = x * SPRITE_SIZE;
				rcScreen.y = y * SPRITE_SIZE;
		        SDL_RenderCopy( renderer, grass, NULL, NULL );
		        //SDL_BlitSurface(grass, NULL, screen, &rcGrass);
			}
		}

		/* draw the sprite */
		//SDL_BlitSurface(sprite, NULL, screen, &rcSprite);
		//Render texture to screen
		SDL_RenderCopy( renderer, sprite, &rcSprite, &rcScreen );

		/* update the screen */
		//SDL_UpdateRect(screen,0,0,0,0);
		SDL_RenderPresent( renderer );
	}

	/* clean up */
	SDL_DestroyTexture( sprite );
	SDL_DestroyTexture( grass );
	SDL_Quit();

	return 0;
}
