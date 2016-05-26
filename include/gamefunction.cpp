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
    string Column1[]={"","artless","bawdy","beslubbering","bootless","churlish","cockered","clouted","craven","currish","dankish","dissembling","droning","errant","fawning","fobbing","froward","frothy","gleeking","goatish","gorbellied","impertinent","jarring","loggerheaded","lumpish"};
    string Column2[]={"","base-court","bat-fowling","beef-witted","beetle-headed","boil-brained","clapper-clawed","clay-brained","common-kissing","crook-pated","dismal-dreaming","dizzy-eyed","doghearted","dread-bolted","earth-vexing","elf-skinned","fat-kidneyed","fen-sucked","flap-mouthed","fly-bitten","folly-fallen","fool-born","full-gorged","guts-griping","half-faced","hasty-witted"};
    string Column3[]={"","apple-john","baggage","barnacle","bladder","boar-pig","bugbear","bum-bailey","canker-blossom","clack-dish","clotpole","coxcomb","codpiece","death-token","dewberry","flap-dragon","flax-wench","flirt-gill","foot-licker","fustilarian","giglet","gudgeon","haggard","harpy","hedge-pig""horn-beast"};
    result += Column1[DiceRoll(1,24)] + " " + Column2[DiceRoll(1,25)] + " " +Column3[DiceRoll(1,24)] +"!";
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

string FoodChoice()
{
    /*
    1.	1d4 strips of jerky
    2.	bull testicles
    3.	chicken breast
    4.	cow tongue
    5.	garlic
    6.	pastry
    7.	piece of fruit
    8.	roll of bread
    9.	vegetable
    10.	wedge of cheese
    */
    string Result ="";
    switch(DiceRoll(1,10))
        {
            case 1:
                Result = to_string(DiceRoll(1,4)) + " Strips of Jerky";
                break;
            case 2:
                Result = "Bull Testicles";
                break;
            case 3:
                Result = "Chicken Breast";
                break;
            case 4:
                Result = "Cow Tongue";
                break;
            case 5:
                Result = "Garlic";
                break;
            case 6:
                Result = "Pastry";
                break;
            case 7:
                Result = "Piece of Fruit";
                break;
            case 8:
                Result = "Roll of Bread";
                break;
            case 9:
                Result = "Vegetable";
                break;
            case 10:
                Result = "Wedge of Cheese";
                break;
            default:
                cout << "Really you cannot choose ? " << endl;
        }
    return Result;
}

string Gems()
{
    string Result = "";
    int Roll = DiceRoll(1,10);
    string Gem[]={"","onyx","amethyst","tiger's eye","garnet","sapphire","jade","emerald","ruby","diamond"};
    if (Roll == 10)
    {
        Result += Gem[DiceRoll(1,9)] + " & " + Gem[DiceRoll(1,9)];
    }
    else
    {
        Result += Gem[Roll];
    }
    return Result;
}

string Precious()
{
    string Result = "";
    string Metal[]={"","copper","silver","electrum","gold","platimun"};
    int Roll = DiceRoll();
    if (Roll == 6)
    {
        Result += Metal[DiceRoll(1,5)] + " encrusted with "+Gems() ;
    }
    else
    {
        Result += Metal[Roll];
    }
    return Result;
}

string DesignChoice()
{
    string Result = "";
    string Design[]={"","antlers","apples","arcane symbols","arenas","axes","bears","blackberries","boars","bones","bottles","bows","bulls","carnations","cathedrals","cats","chains","chariots","circles","cornstalks","crabs","crowns","crows","demons","dogs","dragons","dwarves","eagles","elements","elves","eye of terror","eyes","fish","flagons","flames","flutes","foxes","frogs","grapes","griffons","halflings","hammers","hands","hares","helms","holly","horses","knights","knotwork","krakens","lightning","lily pads","lions","lutes","maces","manta rays","melons","mermaids","mistletoe","moon","mosques","pegasi","pies","pipes","pots","pyramids","quill and ink","rams","religious symbols","roses","saints","scales","scorpions","scythes","serpents","sharks","shields","ships","skulls","spears","spirals","squares","stag","star","staves","sun","sun/moon","swords","teardrops","temples","towers","trees","triangles","tridents","trolls","turtles","unicorns","virgins","wheat","wizards","wolves"};
    Result = Design[DiceRoll(1,100)];
    return Result;
}

string JewlleryChoice()
{
    string Result = "";
    string Jewellry[] = {"","anklet","armlet","bracelet","brooch","circlet","earring","hairpin","necklace","pendant","ring","toe ring"};
    int Roll = DiceRoll(1,12);
    if (Roll == 12 )
    {
        Result += Precious() + " "+ Jewellry[DiceRoll(1,11)] + " engraved with " + DesignChoice();
    }
    else
    {
        Result += Precious() + " " + Jewellry[Roll];
    }
    return Result;
}

string InterestingItem()
{
    string Result = "";
    int Roll = DiceRoll();
    string Interesting[]={"","candles","baby's rattle","bottle of perfume","child's doll","comb","dog collar","flask of oil","flint and steel","flute","handkerchief","herbal poultice","iron spike","lock","quill and ink pot","rabbit's foot","sheet of parchment","small mirror","spyglass","thieves' tools","vial of holy water"};
    if (Roll == 1)
    {
        int NewRoll = DiceRoll(1,4);
        if (NewRoll==1)
        {
            Result += to_string(DiceRoll(1,4)) + " Candle";
        }
        else
        {
            Result += to_string(DiceRoll(1,4)) + " Candles";
        }
    }
    else
    {
            Result += Interesting[Roll];
    }
    return Result;
}

string MadeOf()
{
    string Result = "";
    int Roll = DiceRoll();
    string MadeOfMaterial[] ={"","Bone","Wood","Copper","Bronze","Brass"};
    if (Roll == 6)
    {
        Result += Precious();
    }
    else
    {
        Result += MadeOfMaterial[Roll];
    }
    return Result;
}

string ValuableItem()
{
    string Result = "";
    int NewRoll = 0;
    int Roll = DiceRoll(1,12);
    string Valuable[]={"","candlestick","flask","holy symbol","horn","key","letter opener","mug","set of dice","smoking pipe","trinket box"};
    if (Roll == 11)
    {
        NewRoll = DiceRoll(1,11);
        if (NewRoll == 11)
        {
            Result += MadeOf() + " " + Valuable[DiceRoll(1.,10)] + " engraved with " + DesignChoice() + " inlaid with " + Precious();
        }
        else
        {
            Result +=MadeOf() + " " + Valuable[DiceRoll(1.,10)] + " engraved with " + DesignChoice() ;

        }
    }
    else if(Roll == 12)
    {
        NewRoll = DiceRoll(1,11);
        if (NewRoll == 11)
        {
            Result +=MadeOf() + " " + Valuable[DiceRoll(1.,10)] + " engraved with " + DesignChoice() + " inlaid with " + Precious();
        }
        else
        {
            Result += MadeOf() + " " + Valuable[DiceRoll(1.,10)] + " engraved with " + DesignChoice() ;

        }
    }
    else
    {
        Result += MadeOf()+" "+Valuable[Roll];
    }
    return Result;
}

string UnwantedItem()
{
    string Result = "";
    int Roll=DiceRoll(1,20);
    string Unwanted[]={"","15 fake gold coins","bag of goat eyes","bead necklace covered in feces","bloody glove","bundle of dog poo","clump of poison ivy","fingernail clippings wrapped in cloth","flag with standard of Xanne","flask of deer urine","folded paper with 'Death to the Duke!' written on it","grimy wooden dentures","head lice","holy symbol of Chaos and Destruction","maggoty pork wrapped in cloth","poisonous snake","severed finger inside a biscuit","small sack with dead kitten inside","soiled adult diaper","tobacco pouch made of tattooed human skin","vial of sour breast milk"};
    Result += Unwanted[Roll];
    return Result;
}


string PickPocket()
{
    /*
    1.	Food
    2.	Jewelry
    3.	Gem
    4.	Interesting Item
    5.	Valuable Item
    6.	Unwanted Item
    */
    string Result = "";
    switch(DiceRoll())
        {
            case 1:
                Result += "Food: " + FoodChoice();
                break;
            case 2:
                Result += "Jewellry: " + JewlleryChoice();
                break;
            case 3:
                Result += "Gem: "+ Gems();
                break;
            case 4:
                Result += "Interesting Item: "+ InterestingItem();
                break;
            case 5:
                Result += "Valuable Item: "+ValuableItem();
                break;
            case 6:
                Result += "Unwanted Item :"+ UnwantedItem();
                break;
            default:
                cout << "Really you cannot choose ? " << endl;
        }
    return Result;
}