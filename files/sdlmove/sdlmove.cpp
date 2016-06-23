#include "SDL2/SDL.h"


#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE    32
#define SCREEN_TITLE  "SDL Move"
int main(int argc, char* argv[])
{
	SDL_Surface     *temp;
	SDL_Window*     screen = NULL;
	SDL_Renderer*   renderer = NULL;
	SDL_Texture*    sprite = NULL;
	SDL_Texture*    grass = NULL;
	SDL_Rect        rcSprite, rcGrass;
	SDL_Event       event;

	const unsigned char   *keystate;
	int             colorkey, gameover;

	/* initialize video system */
	SDL_Init(SDL_INIT_VIDEO);

	/* set the title bar */
	// SDL_WM_SetCaption("SDL Move", "SDL Move");
	// replaced by SCREEN_TITLE

	/* create window */
	//screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    screen = SDL_CreateWindow( SCREEN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( screen, -1, SDL_RENDERER_ACCELERATED );
	/* load sprite */
	temp   = SDL_LoadBMP("sprite.bmp");
	//sprite = SDL_DisplayFormat(temp);
	sprite = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	/* setup sprite colorkey and turn on RLE */
	//SDL_PixelFormat* myPixelFormat=temp->format;
	//colorkey = SDL_MapRGB(myPixelFormat, 255, 0, 255);
	//SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

	/* load grass */
	temp  = SDL_LoadBMP("grass.bmp");
	//grass = SDL_DisplayFormat(temp);
	grass = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	/* set sprite position */
	rcSprite.x = 0;
	rcSprite.y = 0;

	gameover = 0;

	/* message pump */
	while (!gameover)
	{
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

		/* collide with edges of screen */
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

		/* draw the grass */
		for (int x = 0; x < SCREEN_WIDTH/SPRITE_SIZE; x++) {
			for (int y = 0; y < SCREEN_HEIGHT/SPRITE_SIZE; y++) {
				rcGrass.x = x * SPRITE_SIZE;
				rcGrass.y = y * SPRITE_SIZE;
				//SDL_BlitSurface(grass, NULL, screen, &rcGrass);
			}
		}
		//Clear screen
		//SDL_RenderClear( renderer );

		/* draw the sprite */
		//SDL_BlitSurface(sprite, NULL, screen, &rcSprite);
		//Render texture to screen
		SDL_RenderCopy( renderer, sprite, NULL, NULL );

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
