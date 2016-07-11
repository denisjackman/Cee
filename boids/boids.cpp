/*
Name        :   boids.cpp
Author      :   Denis Jackman
Date        :   07/07/2016
Version     :   10:43:00
Function    :   This is a flocking modeller for Bird Androids (Boids) passed on a number of references
Compile     :   make
                g++ ../include/general.cpp ../include/SDLEngine.cpp ../include/gamefunction.cpp boids.cpp -w -std=gnu++0x -I/usr/local/include -L/usr/local/lib  -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o boids

Change History
Name        :   Date        :   Version :   Reason
D Jackman   :   07/07/2016  :   1:00:00 :   Original Version
D Jackman   :   11/07/2016  :   1.01:00 :   Added new direction NW,NE, SW,SE and rejigged the vectors (X,Y) is now at
                                            center of the vector

To Do List
TODO: 001 Add the rules
TODO: 002 Add Extra Rules
TODO: 003 Add goals for the boids to move toward
TODO: 004 Add wind or current that "blows" the boids around
TODO: 005 Have boids tend towards a place; travel through waypoints
TODO: 006 Limit (or unlimit) a boid's speed
TODO: 007 Set bounds for boids
TODO: 008 Allow boids to "perch" on the ground at random.
TODO: 009 anti-flocking behaviour
TODO: 010 Get the boid group to scatter from each other; add more rules
TODO: 011 Send the boids away from certain areas; danger or obstacles
TODO: 012 Introduce predators that boids will always run from
TODO: 013 some other details
TODO: 014 Boids need to "see" each other
TODO: 015 Unseen boids should be ignored
TODO: 016 Refer to the original algorithm
TODO: 017 The timing engine needs redesign
TODO: 018 Change updating system to that used by QuizMe

Reference Material
001 http://www.red3d.com/cwr/papers/1987/boids.html
002 http://www.red3d.com/cwr/boids/
003 http://www.red3d.com/cwr/nobump/nobump.html
004 http://harry.me/blog/2011/02/17/neat-algorithms-flocking/
005 https://processing.org/examples/flocking.html
006 https://codea.io/talk/discussion/697/boids-a-simple-implementation-of-flocking-behaviors
007 http://natureofcode.com/book/chapter-6-autonomous-agents/
008 http://lyndonarmitage.com/boids-flocking-behaviour-tutorial-part-1-the-engine/
*/

/*
Basic Rules for Boids:
    Separation:     Avoid crowding local flock members.
    Alignment:      Keep to the Average direction of the flock.
    Cohesion:       Keep to an average position of the flock.
*/

/*
Boid Attributes:
    Direction
    Speed
    IsLeader
*/

/*
General Variables:
    Separation Distance:
    Cohesion Distance:
    Leader Colour:
    Flock Colour:

 Headings reminder
     east      : 0
     south     : 1
     west      : 2
     north     : 3
     northeast : 4
     southwest : 6
     northwest : 5
     southeast : 7

*/

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
#include "../include/general.h"
#include "../include/gamefunction.h"
#include "../include/SDLEngine.h"
#include "boid.h"

namespace mapping
{
    enum direction_t
    {
        east,
        south,
        west,
        north,
        northeast,
        northwest,
        southwest,
        southeast
    };
}

using namespace std;
using namespace mapping;

void renderBird(int x, int y, customcolour colour, int width = 5);
void renderLineBird(int x, int y, customcolour colour, int width = 5, direction_t dir = east);

//Main code
int main (int argc, char* args[] )
{
    SCREEN_WIDTH        = 1200;
    SCREEN_HEIGHT       = 900;
    SCREEN_TITLE        = "Boids";
    PROGRAM_TIMER       = 2000;
    VERSION             = "V0.00.00";
    NAME_PROGRAM        = "Boids";
    MEDIAFILE           = "../files/texture.png";
    int                 flock = 100;
    Boid                bird[100];
    int                 newheading = 0;
    int                 timing= 100;


  	Print(" -- " + string(NAME_PROGRAM) + " " + string(VERSION) + " (Test) -- ");
	Print(" --- Starting ---");
    srand(time(0));

    if (GameInitialise() == false)
    {
        Print("Game failed to initialise !");
    }
    else
    {
        //Main loop flag
        bool boidLoop = true;
        //Event handler
        SDL_Event boidEvent;
        //While application is running
	    while ( boidLoop )
    	{
	        //Handle events on queue
		    while ( SDL_PollEvent(&boidEvent ) != 0 )
		    {
			    //User requests quit
			    if ( boidEvent.type == SDL_QUIT)
			    {
				    boidLoop = false;
			    }
		    }
		    ClearScreen(Black);
			//Clear screen
			SDL_RenderClear( gRenderer );
            for(int loop = 0; loop < flock; loop++)
            {
        
                renderLineBird(bird[loop].posx(), bird[loop].posy(), Yellow, 20, direction_t(bird[loop].heading()) );
    
                switch(bird[loop].heading())
                {
                    case east:
                    {
                        // East
                        bird[loop].setx(bird[loop].posx() + 1);
                        break;
                    }
                    case south:
                    {
                        // South
                        bird[loop].sety(bird[loop].posy() + 1);
                        break;
                    }
                    case west:
                    {
                        // West
                        bird[loop].setx(bird[loop].posx() - 1);
                        break;
                    }
                    case north:
                    {
                        // North
                        bird[loop].sety(bird[loop].posy() - 1);
                        break;
                    }
                    case northeast:
                    {
                        // North East
                        bird[loop].setx(bird[loop].posx() + 1);
                        bird[loop].sety(bird[loop].posy() - 1);
                        break;
                    }
                    case northwest:
                    {
                        // North West
                        bird[loop].setx(bird[loop].posx() - 1);
                        bird[loop].sety(bird[loop].posy() - 1);
                        break;
                    }
                    case southeast:
                    {
                        // South East
                        bird[loop].setx(bird[loop].posx() + 1);
                        bird[loop].sety(bird[loop].posy() + 1);
                        break;
                    }
                    case southwest:
                    {
                        // South West
                        bird[loop].setx(bird[loop].posx() - 1);
                        bird[loop].sety(bird[loop].posy() + 1);
                        break;
                    }
                }
    
                if (bird[loop].posy() > SCREEN_HEIGHT)
                {
                    bird[loop].sety(0);
                }
                if (bird[loop].posy() < 0)
                {
                    bird[loop].sety(SCREEN_HEIGHT);
                }
    
                if (bird[loop].posx() > SCREEN_WIDTH)
                {
                    bird[loop].setx(0);
                }
                if (bird[loop].posx() < 0)
                {
                    bird[loop].setx(SCREEN_WIDTH);
                }
                timing = timing - 1;
                if (timing < 0)
                {
                    timing = 100;
                    bird[loop].setdirection(rand() % 8);
                }
             }
            //Render texture to screen
			SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

			//Update screen
			SDL_RenderPresent( gRenderer );
	     }
	}
	GameTerminate();
	Print(" --- Ending ---");
  	return 0;
}

void renderBird(int x, int y, customcolour colour, int width)
{
    SDL_Rect birdRect = { x, y, width , width  };
    SDL_SetRenderDrawColor( gRenderer, colour.red , colour.green , colour.blue, 0xFF );
    SDL_RenderFillRect( gRenderer, &birdRect );
}

void renderLineBird(int x, int y, customcolour colour, int width, direction_t dir  )
{
    int ax;
    int ay;
    int bx;
    int by;
    int cx;
    int cy;
    switch(dir)
    {
        case east:
        {
            // East
            ax = x - (width/2);
            ay = y - (width/2);
            bx = x + (width/2);
            by = y;
            cx = x - (width/2);
            cy = y + (width/2);
            break;
        }
        case south:
        {
            // South
            ax = x - (width/2);
            ay = y - (width/2);
            bx = x + (width/2);
            by = y - (width/2);
            cx = x ;
            cy = y + (width/2);
            break;
        }
        case west:
        {
            // West
            ax = x - (width/2);
            ay = y;
            bx = x + (width/2);
            by = y - (width/2);
            cx = x + (width/2);
            cy = y + (width/2);
            break;
        }
        case north:
        {
            // North
            ax = x;
            ay = y - (width/2);
            bx = x + (width/2);
            by = y + (width/2);
            cx = x - (width/2);
            cy = y + (width/2) ;
            break;
        }
        case northeast:
        {
            // North East
            ax = x + (width/2);
            ay = y - (width/2);
            bx = x;
            by = y + (width/2);
            cx = x - (width/2);
            cy = y;
            break;
        }
        case northwest:
        {
            // North West
            ax = x - (width/2);
            ay = y - (width/2);
            bx = x + (width/2);
            by = y;
            cx = x;
            cy = y + (width/2);
            break;
        }
        case southeast:
        {
            // South East
            ax = x;
            ay = y - (width/2);
            bx = x + (width/2);
            by = y + (width/2);
            cx = x - (width/2);
            cy = y ;
            break;
        }
        case southwest:
        {
            // South West
            ax = x;
            ay = y - (width/2);
            bx = x + (width/2);
            by = y;
            cx = x - (width/2);
            cy = y + (width/2) ;
            break;
        }
     }
    SDL_SetRenderDrawColor( gRenderer, colour.red , colour.green , colour.blue, 0xFF );
    SDL_RenderDrawLine( gRenderer, ax, ay, bx, by );
    SDL_RenderDrawLine( gRenderer, bx, by, cx, cy );
    SDL_RenderDrawLine( gRenderer, cx, cy, ax, ay );

}
