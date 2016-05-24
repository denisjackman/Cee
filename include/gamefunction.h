#ifndef GAMEFUNCTION_H
#define GAMEFUNCTION_H

using namespace std;

int DiceRoll(int rolls = 1, int sides = 6);
int DistanceToTarget(double oX0, double oY0, double tX1, double tY1);
string InsultGenerator();
string IntegerToRoman(int number);
int RomanToInteger(string roman);
int Rating(int totalRating, int playerWins, int playerLosses, int playerGames);

#endif