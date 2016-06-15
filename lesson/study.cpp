#include <string>
#include <iostream>
using namespace std;

typedef unsigned long  int32u;
typedef long	       int32;
typedef unsigned short int16u;
typedef short	       int16;
typedef unsigned char  int8u;

// Defence items
#define SLAY_DRAGON     0x0001
#define SLAY_ANIMAL     0x0002
#define SLAY_EVIL       0x0004
#define SLAY_UNDEAD     0x0008
#define FROST           0x0010
#define FIRE            0x0020
#define POISON          0x0040
#define ACID            0x0080
#define LIGHT           0x0100
#define STONE_TO_MUD    0x0200
#define NO_CHARM        0x1000
#define INFRAVISION     0x2000
#define MAX_HIT         0x4000

// Move items
#define MOVE_ATTACK     0x0000001AL
#define MOVE_NORMAL     0x0000002AL
#define MOVE_TWENTY     0x0000008AL
#define MOVE_FORTY      0x0000010AL
#define MOVE_SEVENTY    0x0000020AL
#define MOVE_INVISIBLE  0x0001000AL
#define THRU_DOORS      0x0002000AL
#define PICKUP_OBJECTS  0x0010000AL
#define MULTIPLY_MONST  0x0020000AL
#define CARRIES_OBJECT  0x0100000AL
#define CARRIES_GOLD    0x0200000AL
#define CARRIES_60      0x0400000AL
#define CARRIES_90      0x0800000AL
#define CARRY_RAND1     0x1000000AL
#define CARRY_RAND2     0x2000000AL
#define WIN_GAME        0x8000000AL

// Spells
#define NO_SPELL            0x00000000L
#define FREQ_1              0x00000001L
#define FREQ_2              0x00000002L
#define FREQ_3              0x00000004L
#define FREQ_4              0x00000008L
#define TPORT_BLINK         0x00000010L
#define TPORT_LONG          0x00000020L
#define TPORT_PLAYER        0x00000040L
#define LIGHT_WOUND         0x00000080L
#define SERIOUS_WOUND       0x00000100L
#define PARALYSIS           0x00000200L
#define BLINDNESS           0x00000400L
#define CONFUSION           0x00000800L
#define FEAR                0x00001000L
#define SUMM_MONSTER        0x00002000L
#define SUMM_UNDEAD         0x00004000L
#define SLOW                0x00008000L
#define DRAIN_MANA          0x00010000L
#define BREATHE_LIGHTNING   0x00080000L
#define BREATHE_GAS         0x00100000L
#define BREATHE_ACID        0x00200000L
#define BREATHE_FROST       0x00400000L
#define BREATHE_FIRE        0x00800000L



typedef struct creature_type
{
  char      *name;		/* Descrip of creature	    */
  int32u    cmove;		/* Bit field		        */
  int32u    spells;	    /* Creature spells	        */
  int16u    cdefense;	/* Bit field		        */
  int16u    mexp;		/* Exp value for kill	    */
  int8u     sleep;		/* Inactive counter/10	    */
  int8u     aaf;		/* Area affect radius	    */
  int8u     ac;		    /* AC			            */
  int8u     speed;		/* Movement speed+10	    */
  int8u     cchar;		/* Character rep.	        */
  int8u     hd[2];		/* Creatures hit die	    */
  int8u     damage[4];	/* Type attack and damage   */
  int8u     level;		/* Level of creature	    */
};

int main(int argc, char *argv[])
{
    creature_type urchin;
    creature_type balrog;

    urchin.name    = "Filthy Street Urchin";
    urchin.cmove   = 0x0012000AL;
    // picks up objects
    // can move through doors
    urchin.spells  = 0x00000000L;
    // no spells
    urchin.cdefense= 0x2034;
    // can be seen by infravision
    // can be hurt by fire and frost
    // can be the target of slay evil
    urchin.mexp    = 0;
    urchin.sleep   = 40;
    urchin.aaf     = 4;
    urchin.ac      = 1;
    urchin.speed   = 11;
    urchin.cchar   = 'p';
    urchin.hd[1]   = 1;
    urchin.hd[2]   = 4;
    urchin.damage[1]= 72;
    urchin.damage[2]= 148;
    urchin.damage[3]= 0;
    urchin.damage[4]= 0;
    urchin.level   = 0;

    // {"Balrog"		            ,0xFF1F0002L,0x0081C743L,0x5004,55000L,   0,  40, 125, 13, 'B', {75,40} , {104,78,214,0}	,  100}
    // {"Filthy Street Urchin"	    ,0x0012000AL,0x00000000L,0x2034,    0,  40,   4,	1, 11, 'p', {1,4}   , {72,148,0,0}		,    0},

    if (urchin.cdefense & FROST)
    {
        cout << urchin.name << " can be slain by frost " << endl;
    }
    if (urchin.cdefense & FIRE)
    {
        cout << urchin.name << " can be slain by fire " << endl;
    }
    if (urchin.cdefense & INFRAVISION)
    {
        cout << urchin.name << " can be seen by infravision " << endl;
    }
    if (urchin.cdefense & SLAY_EVIL)
    {
        cout << urchin.name << " can be damaged by slay evil " << endl;
    }
    if (urchin.cmove & THRU_DOORS)
    {
        cout << urchin.name << " can be go through doors " << endl;
    }
    if (urchin.cmove & PICKUP_OBJECTS)
    {
        cout << urchin.name << " can pickup objects " << endl;
    }

}