#ifndef CONSTANTS_H
#define CONSTANTS_H

// Number of monsters available
#define MAX_CREATURE_LIST  279

// Defence items
#define CD_SLAY_DRAGON     0x0001
#define CD_SLAY_ANIMAL     0x0002
#define CD_SLAY_EVIL       0x0004
#define CD_SLAY_UNDEAD     0x0008
#define CD_FROST           0x0010
#define CD_FIRE            0x0020
#define CD_POISON          0x0040
#define CD_ACID            0x0080
#define CD_LIGHT           0x0100
#define CD_STONE_TO_MUD    0x0200
#define CD_NO_CHARM        0x1000
#define CD_INFRAVISION     0x2000
#define CD_MAX_HIT         0x4000

// Move items
#define CM_MOVE_ATTACK     0x00000001AL
#define CM_MOVE_NORMAL     0x00000002AL
#define CM_MOVE_TWENTY     0x00000008AL
#define CM_MOVE_FORTY      0x00000010AL
#define CM_MOVE_SEVENTY    0x00000020AL
#define CM_MOVE_INVISIBLE  0x00001000AL
#define CM_THRU_DOORS      0x00002000AL
#define CM_PICKUP_OBJECTS  0x00010000AL
#define CM_MULTIPLY_MONST  0x00020000AL
#define CM_CARRIES_OBJECT  0x00100000AL
#define CM_CARRIES_GOLD    0x00200000AL
#define CM_CARRIES_60      0x00400000AL
#define CM_CARRIES_90      0x00800000AL
#define CM_CARRY_RAND1     0x01000000AL
#define CM_CARRY_RAND2     0x02000000AL
#define CM_WIN_GAME        0x80000000AL

// Spells
#define CS_NO_SPELL        0x00000000L
#define CS_FREQ_1          0x00000001L
#define CS_FREQ_2          0x00000002L
#define CS_FREQ_3          0x00000004L
#define CS_FREQ_4          0x00000008L
#define CS_TPORT_BLINK     0x00000010L
#define CS_TPORT_LONG      0x00000020L
#define CS_TPORT_PLAYER    0x00000040L
#define CS_LIGHT_WOUND     0x00000080L
#define CS_SERIOUS_WOUND   0x00000100L
#define CS_PARALYSIS       0x00000200L
#define CS_BLINDNESS       0x00000400L
#define CS_CONFUSION       0x00000800L
#define CS_FEAR            0x00001000L
#define CS_SUMM_MONSTER    0x00002000L
#define CS_SUMM_UNDEAD     0x00004000L
#define CS_SLOW            0x00008000L
#define CS_DRAIN_MANA      0x00010000L
#define CS_LIGHTNING       0x00080000L
#define CS_GAS             0x00100000L
#define CS_ACID            0x00200000L
#define CS_FROST           0x00400000L
#define CS_FIRE            0x00800000L

#endif