#include <ncurses.h>
#include <string>
#include <iostream>
#include "../include/gamefunction.h"

using namespace std;
int gScreenWidth = 80;
int gScreenHeight = 40;
int nPlayerX = 10;
int nPlayerY = 10;
int nPlayerInput = 0;
char nPlayer = '@';
bool wGameLoop = true;

void erase( int y, int x)
{
    // displays a '#' is the player trail
    // can be change to a ' ' if needed
    mvaddch(y,x,'#');
    mvaddch(y,x,' ');
}

void initialise()
{
    // Initialise
    initscr();
    clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	if (curs_set(0) == ERR)
	{
	    cout << "ERR-cur_set error " << endl;
	}
}

void checkLimits()
{
    if (nPlayerX > gScreenWidth)
    {
        nPlayerX = gScreenWidth;
    }
    if (nPlayerX < 0)
    {
        nPlayerX = 0;
    }
    if (nPlayerY > gScreenHeight)
    {
        nPlayerY = gScreenHeight;
    }
    if (nPlayerY < 0)
    {
        nPlayerY = 0;
    }
}

void gameloop()
{

    while (wGameLoop)
    {
       // Output Phase goes here
       mvaddch(nPlayerY, nPlayerX, nPlayer);

       // Input phase goes here
       nPlayerInput = getch();

       // Processing Phase goes here
       // Erase the player
       erase(nPlayerY, nPlayerX);
       // process the key press
       switch(nPlayerInput)
       {
            case 'q':
                wGameLoop = false;
                break;
            case 'Q':
                wGameLoop = false;
                break;
            case KEY_RIGHT:
                nPlayerX += 1;
                break;
            case KEY_LEFT:
                nPlayerX -= 1;
                break;
            case KEY_UP:
                nPlayerY -= 1;
                break;
            case KEY_DOWN:
                nPlayerY += 1;
                break;
            default:
                break;
        }

       checkLimits();
    }

}

int main( void)
{
    initialise();
    printw("Welcome to Rogue\nPress any key to continue\nPress 'q' or 'Q' to quit at any time\n");
    nPlayerInput = getch();
    clear();
    gameloop();
    endwin();

    return 0;
}
