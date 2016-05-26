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

    cout << "You have a " << PickPocket() << endl;
    return 0;
}