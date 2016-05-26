#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ncurses.h>
#include "../include/gamefunction.h"

using namespace std;

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
                Result += "Gem";
                break;
            case 4:
                Result += "Interesting Item";
                break;
            case 5:
                Result += "Valuable Item";
                break;
            case 6:
                Result += "Unwanted Item";
                break;
            default:
                cout << "Really you cannot choose ? " << endl;
        }
    return Result;
}

int main(int argc, char *argv[])
{
    vector<string> itemList;
    string line;
    ifstream myfile ("../files/list.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            itemList.push_back(line);
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    cout << "You have a " << FoodChoice() << endl;
    cout << "You have a " << JewlleryChoice() << endl;

  return 0;
}