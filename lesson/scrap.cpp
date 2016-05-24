#include <string>
#include <iostream>
#include "../include/gamefunction.h"

using namespace std;


int main(int argc, char *argv[])
{
    cout << "Win  (1000) :  1400 " << Rating(1000,1,0,1) << endl; 
    cout << "Draw (1000) : 1000 " << Rating(1000,0,0,1) << endl;
    cout << "Win 2 * 1000 : 1400 " << rating(2000,2,0,2) << endl;
    cout << "----"
    cout << "player 1 (1000 wins) "  << Rating(1000,1,0,1) << endl;
    cout << "player 2 (1000 loses) "  << Rating(1000,0,1,1) << endl;
    cout << "player 1 (600 wins again) "  << Rating(600,1,0,1) << endl;    
    return 0;
}