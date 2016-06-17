#ifndef ROGUE_H
#define ROGUE_H

typedef unsigned long  int32u;
typedef long	       int32;
typedef unsigned short int16u;
typedef short	       int16;
typedef unsigned char  int8u;

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

void CreatureDefence(creature_type creature);
void CreatureMove(creature_type creature);
void CreatureSpells(creature_type creature);
void CreatureHitDice(creature_type creature);
void CreatureAttacks(creature_type creature);



#endif