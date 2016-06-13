#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void ClearScreen()
{
    /*
    This will clear the screen
    */
    cout << "\033[2J\033[1;1H";
}

int main(int argc, char *argv[])
{
    srand(time(0));
    string ScreenLine ="";
    string NumberLine = "0123456789";
    int store = 0;
    for ( int x = 1; x < 65; x++ )
    {
        store = rand() % 97 + 33;
        ScreenLine += store;
    }
    for (int y = 1; y < 160; y++)
    {
        cout << ScreenLine;
    }
}