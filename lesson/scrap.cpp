#include <ncurses.h>
int main()
{
    initscr();
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLUE);
    attrset (COLOR_PAIR(1));
    move(12,30);
    printw("My first color prog");
    getch();
    endwin();
    return 0;
}