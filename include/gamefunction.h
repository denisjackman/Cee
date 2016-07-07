#ifndef GAMEFUNCTION_H
#define GAMEFUNCTION_H

/* Game functions */
int DiceRoll(int rolls = 1, int sides = 6);
int DistanceToTarget(double oX0, double oY0, double tX1, double tY1);
std::string InsultGenerator();
int Rating(int totalRating, int playerWins, int playerLosses, int playerGames);

/* Specific Fucntions for RPG */
std::string FoodChoice();
std::string Gems();
std::string Precious();
std::string DesignChoice();
std::string JewlleryChoice();
std::string InterestingItem();
std::string MadeOf();
std::string ValuableItem();
std::string UnwantedItem();
std::string PickPocket();
std::string WHFRPLootCrateList();
std::vector <std::vector <bool> > MazeGen(int mX = 80, int mY = 40);
std::string SciFiShoutOut();

#endif