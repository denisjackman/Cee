#include <string>
#include <iostream>
#include<ctime>
#include<cstdlib>
#include "../include/constants.h"
#include "../include/rogue.h"
#include "../include/monster.h"

using namespace std;

void CreatureAttacks(creature_type creature)
{
        for ( int i = 0; i < 4; i++ )
        {
            if (creature.damage[i] != 0)
            {
                cout << i << " : "<< to_string(creature.damage[1]) << " : " << attack_type[monster_attacks[creature.damage[i]].attack_type] << " - " <<  attack_description[monster_attacks[creature.damage[i]].attack_desc] << " : for between " << \
                to_string(monster_attacks[creature.damage[i]].attack_dice) << " and " << \
                monster_attacks[creature.damage[i]].attack_dice * monster_attacks[creature.damage[i]].attack_sides << endl;
            }
        }
}

int main(int argc, char *argv[])
{
    srand(time(0));
    creature_type monster = creature_list[rand() % 278];
    //creature_type monster = creature_list[0];
    cout << "==" << monster.name << "=="<< endl;
    CreatureDefence(monster);
    cout << "--------------------------------" << endl;
    CreatureMove(monster);
    cout << "--------------------------------" << endl;
    CreatureSpells(monster);
    cout << "--------------------------------" << endl;
    CreatureHitDice(monster);
    cout << "--------------------------------" << endl;
    CreatureAttacks(monster);
}