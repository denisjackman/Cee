#include <string>
#include <iostream>
#include "../include/constants.h"
#include "../include/rogue.h"


using namespace std;

void CreatureDefence(creature_type creature)
{

    if (creature.cdefense & CD_SLAY_DRAGON)
    {
        cout << creature.name << " can be damaged by slay dragon " << endl;
    }
    if (creature.cdefense & CD_SLAY_ANIMAL)
    {
        cout << creature.name << " can be damaged by slay animal " << endl;
    }
    if (creature.cdefense & CD_SLAY_EVIL)
    {
        cout << creature.name << " can be damaged by slay evil " << endl;
    }
    if (creature.cdefense & CD_SLAY_UNDEAD)
    {
        cout << creature.name << " can be damaged by slay undead " << endl;
    }
    if (creature.cdefense & CD_FROST)
    {
        cout << creature.name << " can be slain by frost " << endl;
    }
    if (creature.cdefense & CD_FIRE)
    {
        cout << creature.name << " can be slain by fire " << endl;
    }
    if (creature.cdefense & CD_POISON)
    {
        cout << creature.name << " can be slain by poison" << endl;
    }
    if (creature.cdefense & CD_ACID)
    {
        cout << creature.name << " can be slain by acid " << endl;
    }
    if (creature.cdefense & CD_LIGHT)
    {
        cout << creature.name << " can be slain by light" << endl;
    }
    if (creature.cdefense & CD_STONE_TO_MUD)
    {
        cout << creature.name << " can be slain by stone to mud" << endl;
    }
    if (creature.cdefense & CD_NO_CHARM)
    {
        cout << creature.name << " cannot be charmed" << endl;
    }
    if (creature.cdefense & CD_INFRAVISION)
    {
        cout << creature.name << " can be seen by infravision " << endl;
    }
    if (creature.cdefense & CD_MAX_HIT)
    {
        cout << creature.name << " has maximum hit dice " << endl;
    }
}

void CreatureMove(creature_type creature)
{
    if (creature.cmove & CM_MOVE_ATTACK)
    {
        cout << creature.name << " can move to attack " << endl;
    }
    if (creature.cmove & CM_MOVE_NORMAL)
    {
        cout << creature.name << " can move normally " << endl;
    }
    if (creature.cmove & CM_MOVE_TWENTY)
    {
        cout << creature.name << " can move at 20% speed " << endl;
    }
    if (creature.cmove & CM_MOVE_FORTY)
    {
        cout << creature.name << " can move at 40% speed " << endl;
    }
    if (creature.cmove & CM_MOVE_SEVENTY)
    {
        cout << creature.name << " can move at 470% speed " << endl;
    }
    if (creature.cmove & CM_MOVE_INVISIBLE)
    {
        cout << creature.name << " can move while invisible" << endl;
    }
    if (creature.cmove & CM_THRU_DOORS)
    {
        cout << creature.name << " can be go through doors " << endl;
    }
    if (creature.cmove & CM_PICKUP_OBJECTS)
    {
        cout << creature.name << " can pickup objects " << endl;
    }
    if (creature.cmove & CM_MULTIPLY_MONST)
    {
        cout << creature.name << " can multiply " << endl;
    }
    if (creature.cmove & CM_CARRIES_OBJECT)
    {
        cout << creature.name << " will carry an object " << endl;
    }
    if (creature.cmove & CM_CARRIES_GOLD)
    {
        cout << creature.name << " will carry gold " << endl;
    }
    if (creature.cmove & CM_CARRIES_60)
    {
        cout << creature.name << " will carry object 60% of the time " << endl;
    }
    if (creature.cmove & CM_CARRIES_90)
    {
        cout << creature.name << " will carry object 90% of the time " << endl;
    }
    if (creature.cmove & CM_CARRY_RAND1)
    {
        cout << creature.name << " will carry one random object" << endl;
    }
    if (creature.cmove & CM_CARRY_RAND2)
    {
        cout << creature.name << " will carry two random objects" << endl;
    }
    if (creature.cmove & CM_WIN_GAME)
    {
        cout << creature.name << " is a Game Winner!" << endl;
    }
}

void CreatureSpells(creature_type creature)
{
    int spellfreq = 0;
    if (creature.cmove & CS_FREQ_1)
    {
        spellfreq += 1;
    }
    if (creature.cmove & CS_FREQ_2)
    {
        spellfreq += 2;
    }
    if (creature.cmove & CS_FREQ_3)
    {
        spellfreq += 4;
    }
    if (creature.cmove & CS_FREQ_4)
    {
        spellfreq += 8;
    }
    if (creature.cmove & CS_NO_SPELL)
    {
        cout << creature.name << " Cannot cast spells" << endl;
    }
    cout << creature.name << " has a spell frequency of "<< spellfreq << endl;

    if (creature.cmove & CS_TPORT_BLINK)
    {
        cout << creature.name << " can cast Blink!" << endl;
    }
    if (creature.cmove & CS_TPORT_LONG)
    {
        cout << creature.name << " can cast Teleport Self!" << endl;
    }
    if (creature.cmove & CS_TPORT_PLAYER)
    {
        cout << creature.name << " can cast Teleport Player!" << endl;
    }
    if (creature.cmove & CS_LIGHT_WOUND)
    {
        cout << creature.name << " can cast Light Wound" << endl;
    }
    if (creature.cmove & CS_SERIOUS_WOUND)
    {
        cout << creature.name << " can cast Serious Wound" << endl;
    }
    if (creature.cmove & CS_PARALYSIS)
    {
        cout << creature.name << " can cast Paralysis!" << endl;
    }
    if (creature.cmove & CS_BLINDNESS)
    {
        cout << creature.name << " can cast Blindness!" << endl;
    }
    if (creature.cmove & CS_CONFUSION)
    {
        cout << creature.name << " can cast Confusion!" << endl;
    }
    if (creature.cmove & CS_FEAR)
    {
        cout << creature.name << " can cast Fear!" << endl;
    }
    if (creature.cmove & CS_SUMM_MONSTER)
    {
        cout << creature.name << " can cast Summon Monster!" << endl;
    }
    if (creature.cmove & CS_SUMM_UNDEAD)
    {
        cout << creature.name << " can cast Summon Undead!" << endl;
    }
    if (creature.cmove & CS_SLOW)
    {
        cout << creature.name << " can cast Slow!" << endl;
    }
    if (creature.cmove & CS_DRAIN_MANA)
    {
        cout << creature.name << " can cast Drain Mana!" << endl;
    }
    if (creature.cmove & CS_LIGHTNING)
    {
        cout << creature.name << " can cast Lightning!" << endl;
    }
    if (creature.cmove & CS_GAS)
    {
        cout << creature.name << " can cast Gas!" << endl;
    }
    if (creature.cmove & CS_ACID)
    {
        cout << creature.name << " can cast Acid!" << endl;
    }
    if (creature.cmove & CS_FROST)
    {
        cout << creature.name << " can cast Frost!" << endl;
    }
    if (creature.cmove & CS_FIRE)
    {
        cout << creature.name << " can cast Fire!" << endl;
    }
}

void CreatureHitDice(creature_type creature)
{
    cout << creature.name << " has between " << to_string(creature.hd[1]) << " and " << creature.hd[1] * creature.hd[2] << " HP " << endl;
}
void CreatureAttacks(creature_type creature)
{
    
}