#include <string>
#include <iostream>
#include<ctime>
#include<cstdlib>
#include "../include/constants.h"
#include "../include/rogue.h"
#include "../include/monster.h"

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(0));
    creature_type urchin = creature_list[rand() % 278];
    cout << "==" << urchin.name << "=="<< endl;
    CreatureDefence(urchin);
    cout << "--------------------------------" << endl;
    CreatureMove(urchin);
    cout << "--------------------------------" << endl;
    CreatureSpells(urchin);
    cout << "--------------------------------" << endl;
    CreatureHitDice(urchin);
    cout << "--------------------------------" << endl;
}