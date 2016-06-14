#include <ncurses.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "../include/gamefunction.h"

using namespace std;
int gScreenWidth = 80;
int gScreenHeight = 40;
int nPlayerX = 10;
int nPlayerY = 10;
int nPlayerInput = 0;
char nPlayer = '@';
bool wGameLoop = true;

string precode = "\033[";
string blink = "5";
string bold = "1";
string foregroundcolour = "4";
string textcolour = "3";
string postcode = "m";
string aftercode = "\033[0m";

//ansi colour list
string black = "0";
string red = "1";
string green = "2";
string yellow = "3";
string blue = "4";
string magenta = "5";
string cyan = "6";
string white = "7";
string cPlayer = bold +";"+ textcolour + red +"@" +aftercode ;
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
    DebugModeInitialise();
    initscr();
    clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	if (curs_set(0) == ERR)
	{
	    Print("ERR-cur_set error ");
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
    Print("Starting");
    printw("Welcome to Rogue\nPress any key to continue\nPress 'q' or 'Q' to quit at any time\n");
    nPlayerInput = getch();
    clear();
    gameloop();
    endwin();
    Print("Finishing");
    DebugModeTerminate();
    return 0;
}
