#include <string>
#include <iostream>
#include "../include/gamefunction.h"

using namespace std;

string Insult()
{
    string result = "Thou ";
    string Column1[]={"artless","bawdy","beslubbering","bootless","churlish","cockered","clouted","craven","currish","dankish","dissembling","droning","errant","fawning","fobbing","froward","frothy","gleeking","goatish","gorbellied","impertinent","jarring","loggerheaded","lumpish"};
    string Column2[]={"base-court","bat-fowling","beef-witted","beetle-headed","boil-brained","clapper-clawed","clay-brained","common-kissing","crook-pated","dismal-dreaming","dizzy-eyed","doghearted","dread-bolted","earth-vexing","elf-skinned","fat-kidneyed","fen-sucked","flap-mouthed","fly-bitten","folly-fallen","fool-born","full-gorged","guts-griping","half-faced","hasty-witted"};
    string Column3[]={"apple-john","baggage","barnacle","bladder","boar-pig","bugbear","bum-bailey","canker-blossom","clack-dish","clotpole","coxcomb","codpiece","death-token","dewberry","flap-dragon","flax-wench","flirt-gill","foot-licker","fustilarian","giglet","gudgeon","haggard","harpy","hedge-pig""horn-beast"};
    result += Column1[DiceRoll(1,24)] + " " + Column2[DiceRoll(1,25)] + " " +Column3[DiceRoll(1,24)] +"!";
    return result;
}

int main(int argc, char *argv[])
{
    cout << Insult() << endl;
    return 0;
}