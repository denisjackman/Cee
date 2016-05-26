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
string JewlleryChoice()

{
    string Result = "";
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
                Result += "Jewellry";
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

    cout << "You have " << PickPocket() << " " << endl;

  return 0;
}