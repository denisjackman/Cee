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
    int store = 0;
    for ( int x = 1; x < 7; x++ )
    {
        store = rand() % 10 + 166;
        cout << store << endl;
        ScreenLine += store;
    }
    cout << ScreenLine << endl;
    for (int y = 1; y < 78; y++)
    {
        cout << ScreenLine;
    }
}