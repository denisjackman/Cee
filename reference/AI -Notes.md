## Introduction
This is a set of basic notes on the AI for a game object.
This is the flow of logic.

## AI BLOCK
    *   Does the object have a current ORDER?
        If YES then Skip to the ORDER Block
        If NO then continue
    *   Is the Object a LEADER
        If YES Then set the LEADER Flag to TRUE
        If NO the Continue
    *   Let the object SCAN to the limit of it's RANGE
        If there is an ENEMY in WEAPONS range then set the ORDER 
        to ATTACK the ENEMY (using the ID)
        If there is an ENEMY is SCAN range then set the ORDER 
        to FOLLOW the ENEMY (Using the ID)
        If there is no ENEMY in range and there is a FRIEND in range 
        and that FRIEND is a LEADER set the order to FOLLOW the FRIEND 
        (using the ID)
        If there is no ENEMY in range and there is a FRIEND in range 
        and that FRIEND is not a LEADER set the order to FOLLOW 
        the FRIEND (using the ID)

## ORDER BLOCK
    *   Check that the target of the order is still ALIVE
    *   if the target is DEAD erase the ORDER - Carry out a 
        MOVE order in a RANDOM direction at SPEED.
    *   If the target is ALIVE execute the ORDER
    *   Execute the ORDER.

## MOVE

## ATTACK

## FOLLOW

## SCAN
    *   Scan works as follows. The object scans in 360 degree. All object in the range are catalogued.
    *   IFF (Identify Friend or Foe)
    *   If FRIEND is it a LEADER?
        and RANGE
    *   This list should be sorted by RANGE (to give us nearest ENEMY and FRIEND)
