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

   vector <vector <bool> > bmaze = MazeGen();
   // Done
   for (size_t y=0;y<40;y++)
   {
           cout << endl;
           for (size_t x=0;x<80;x++)
           {
                   if (bmaze[y][x]==true)
                           cout << ".";
                   else
                           cout << "#";
           }
   }
   cout << endl;

    return 0;
}