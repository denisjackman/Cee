#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include "../include/gamefunction.h"

using namespace std;
int main(int argc, char *argv[])
{
    bool atkCrit = false;
    bool defCrit = false;
    cout << "Starting Program Run" << endl;
    int atkRoll = DiceRoll(1,20);
    srand(time(NULL));    
    if (atkRoll==20)
    {
	atkCrit = true;
	cout << "Attacker Critical !! " << endl;
    }
    int defRoll = DiceRoll(1,20);
    if (defRoll==20)
    {
        defCrit = true;
        cout << "Defender Critical !! " << endl;
    }
    if (atkRoll == defRoll)
    {
       cout << " Its a Draw! atk:"<< atkRoll<< " def:" << defRoll  << endl;
    }
    cout << "Result - atk:"<< atkRoll<< " def:" << defRoll  << endl;
    cout << "Finished Program Run" << endl;
    return 0;
}
