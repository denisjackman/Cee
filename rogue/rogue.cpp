#include <conio.h>
#include "Console.h"
#include "../include/gamefunction.h"

int main( void)
{
    console.Clear();
    int nPlayerX = 40;
    int nPlayerY = 12;
    bool wGameLoop = true;
    while (wGameLoop)
    {
        // Output Phase goes here
        console.Clear();
        console.Position(nPlayerX, nPlayerY);
        console << '@';

        // Input phase goes here
        KEYPRESS    sKeyPress = console.WaitForKeypress();

        // Processing Phase goes here
        switch( sKeyPress.eCode )
        {
            // Move down
            case CONSOLE_KEY_DOWN:
                nPlayerY++;
                break;

            // Move left
            case CONSOLE_KEY_LEFT:
                nPlayerX--;
                break;
            // Move right
            case CONSOLE_KEY_RIGHT:
                nPlayerX++;
                break;

            // Move up
            case CONSOLE_KEY_UP:
                nPlayerY--;
                break;
            // Quit
            case CONSOLE_KEY_ESCAPE:
                return 0;
            // Ignore any other key
            default:
                break;
        }
    }
    return 0;
}
