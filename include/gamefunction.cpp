#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

int DiceRoll(int rolls = 1, int sides = 6)
{
	int result = 0;
	srand(time(NULL));
	for ( int loop =0; loop < rolls; loop = loop + 1)
	{
        	result += rand() % sides + 1;
	}
	return result;
}

int DistanceToTarget(double oX0, double oY0, double tX1, double tY1)
{
    double result = 0;
    result = sqrt((tX1 - oX0)*(tX1 - oX0) + (tY1 - oY0)*(tY1 - oY0));
    return int(result);
}

string InsultGenerator()
{
    string result = "Thou ";
    string Column1[]={"artless","bawdy","beslubbering","bootless","churlish","cockered","clouted","craven","currish","dankish","dissembling","droning","errant","fawning","fobbing","froward","frothy","gleeking","goatish","gorbellied","impertinent","jarring","loggerheaded","lumpish"};
    string Column2[]={"base-court","bat-fowling","beef-witted","beetle-headed","boil-brained","clapper-clawed","clay-brained","common-kissing","crook-pated","dismal-dreaming","dizzy-eyed","doghearted","dread-bolted","earth-vexing","elf-skinned","fat-kidneyed","fen-sucked","flap-mouthed","fly-bitten","folly-fallen","fool-born","full-gorged","guts-griping","half-faced","hasty-witted"};
    string Column3[]={"apple-john","baggage","barnacle","bladder","boar-pig","bugbear","bum-bailey","canker-blossom","clack-dish","clotpole","coxcomb","codpiece","death-token","dewberry","flap-dragon","flax-wench","flirt-gill","foot-licker","fustilarian","giglet","gudgeon","haggard","harpy","hedge-pig""horn-beast"};
    result += Column1[DiceRoll(1,23)] + " " + Column2[DiceRoll(1,24)] + " " +Column3[DiceRoll(1,23)] +"!";
    return result;
}

string IntegerToRoman(int number)
{
   /*
    converts any given integer to Roman numerals.
    accepts an integer as input and returns a string.

    table = [['M', 1000],
             ['CM', 900],
             ['D', 500],
             ['CD', 400],
             ['C', 100],
             ['XC', 90],
             ['L', 50],
             ['XL', 40],
             ['X', 10],
             ['IX', 9],
             ['V', 5],
             ['IV', 4],
             ['I', 1]]
    for pair in table:
        while integer-pair[1] >= 0:
            integer -= pair[1]
            returnstring += pair[0]
    */
    string result = "";
    return result;
}
int RomanToInteger(string roman)
{
    /*
    converts a given string from Roman numerals to an integer
    accepts a string as input and return an integer

    table = [['M', 1000],
             ['CM', 900],
             ['D', 500],
             ['CD', 400],
             ['C', 100],
             ['XC', 90],
             ['L', 50],
             ['XL', 40],
             ['X', 10],
             ['IX', 9],
             ['V', 5],
             ['IV', 4],
             ['I', 1]]

    for pair in table:
        continual = True
        while continual:
            if len(string) >= len(pair[0]):
                if string[0:len(pair[0])] == pair[0]:
                    returnint += pair[1]
                    string = string[len(pair[0]):]
                else:
                    continual = False
            else:
                continual = False
    */
    int result = 0;
    return result;
}
int Rating(int totalRating, int playerWins, int playerLosses, int playerGames)
{
    /*
    This program is a a performance rating function
    Performance Rating is a hypothetical rating that would result from the games of a single event only. Some chess organizations use the "algorithm of 400" to calculate performance rating. According to this algorithm, performance rating for an event is calculated by taking (1) the rating of each player beaten and adding 400, (2) the rating of each player lost to and subtracting 400, (3) the rating of each player drawn, and (4) summing these figures and dividing by the number of games played.
    Example:    2 Wins, 2 Losses
                (w+400 + x+400 + y-400 + z-400)/4
                [w+x+y+z+400(2)-400(2)]/4
    This can be expressed by the following formula: Performance rating = [((Total of opponents' ratings) + 400 * (Wins - Losses)) / Games].
    Example: If you beat a player with an elo rating of 1000,
        Performance rating = (1000 + 400*1)/1 = 1400
    If you beat two players with elo ratings of 1000,
        Performance rating = (2000 + 400*2)/2 = 1400
    If you draw,
        Performance rating = (1000 + 400*0)/1 = 1000

    This is a function to return a performance rating for a player
    you pass the total rating for the players played
    the number of wins
    number of losses
    number of games
    and it calculates and return the new rating
    a win  - rating(1000,1,0,1) should return 1400
    a draw - rating(1000,0,0,1)
    a win against 2 players (2 * 1000) rating(2000,2,0,2)) should return 1400
    '''
    NewRating = ((totalRating)+ 400 * (playerWins-playerLosses))/playerGames
    return NewRating

if __name__ == "__main__":
    print "Win  (1000) :  1400 " + str(rating(1000,1,0,1))
    print "Draw (1000) : 1000 " +str(rating(1000,0,0,1))
    print "Win 2 * 1000 : 1400 " +str(rating(2000,2,0,2))
    print "----"
    print "player 1 (1000 wins) " +str(rating(1000,1,0,1))
    print "player 2 (1000 loses) " + str(rating(1000,0,1,1))
    print "player 1 (600 wins again) " +str(rating(600,1,0,1))
    */
    int NewRating = 0;
    NewRating = ((totalRating)+ 400 * (playerWins-playerLosses))/playerGames;
    return NewRating;
}