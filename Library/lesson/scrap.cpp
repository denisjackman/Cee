#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ncurses.h>
#include "../include/gamefunction.h"

using namespace std;



int main(int argc, char *argv[])
{
    vector<string> itemList;
    string line;
    ifstream myfile ("../files/list.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            itemList.push_back(line);
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    /*
    int gameX =100;
    int gameY =60;
    vector <vector <bool> > bmaze = MazeGen(gameX,gameY);
    // Done
    for (size_t y=0;y<gameY;y++)
    {
        cout << endl;
        for (size_t x=0;x<gameX;x++)
        {
            if (bmaze[y][x]==true)
                cout << ".";
            else
                cout << "#";
        }
    }
    cout << endl;
    */
    cout << SciFiShoutOut() << endl;

    return 0;
}