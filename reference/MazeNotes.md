So we start with a dungeon X wide and of Y height.
We divide X  by 10 (discard the remainder)
We divide Y by 10 (and again discard the remainder)
These two numbers are muliplied to give the number of Zones in the Dungeon.
The number of Zones divided by the width is the number of rooms.
Room 1 is always the main room.
for the number of rooms we cycle through them.
We establish if the room is Small, Medium, Large or Huge.
There are limits (based on the number of rooms ) on how many of each there can be .
A huge room can be up to 40 wide and 40 Heigh  - minimum is 20
A large room can be up to 25 wide and 25 heigh - minimum is 15
a medium room can be up to 20 wide and 20 heigh - minimun is 10
A small room can be up to 15 wide and 15 heigh - minimum is 5.

1-9 Rooms (1 Huge, 1 large, 2-4 medium, 2-4 small)
10-20 rooms (1-3 Huge, 1-5 large, 1-4 medium, 1-4 small)

Once the rooms are placed (none should overlap)
Doors can be established

1-2 Small rooms
1-4 Medium rooms
2-6 Large Room
2-8 Huge rooms

Starting with the main room - connect a door to another door in another room
Continue until all doors are used

