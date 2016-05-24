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
    string result = "";
    return result;
}
int RomanToInteger(string roman)
{
    int result = 0;
    return result;
}