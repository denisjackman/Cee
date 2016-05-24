#include <string>
#include <iostream>
#include <ncurses.h>

using namespace std;
int main(int argc, char *argv[])
{
    curs_set(0);
    refresh();
    printw("Welcome to Rogue\nPress any key to continue\nPress 'q' or 'Q' to quit at any time\n");
    nPlayerInput = getch();
    clear();

    curs_set(1);
    endwin();

}