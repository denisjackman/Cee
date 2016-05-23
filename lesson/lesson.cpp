#include <iostream>
#include "../include/gamefunction.h"

using namespace std;

int main (int argc, char* args[] )
{
    cout << "Welcome to the Guess a number game " << endl;
    cout << "I will choose a number between one and one hundred " << endl;
    cout << "And I will ask you to guess it. " << endl << endl;
    cout << "Good Luck " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Thinking of a number " << endl;
    int Answer = DiceRoll(1,100);
    int Guess = 0;
    int Tries = 0;
    bool GameLoop = true;
    cout << "OK got it - here we go  " << endl;
    while (GameLoop)
    {
        Tries += 1;
        cout << "Try number " << Tries << endl;
        cout << "Please guess a number ";
        cin >> Guess;
        if (Guess > 100)
        {
            cout << "Really ? between one and a hundred and you give me " << Guess << endl;
        }
        else if (Guess > Answer)
        {
            cout << "Oooooooh ! It's lower than  " << Guess << endl;
        }
        else if (Guess < Answer)
        {
            cout << "Almost! It's higher than  " << Guess << endl;
        }
        else if (Guess == Answer)
        {
            cout << "Spot on ! the answer was  " << Guess << endl;
            cout << "you did it in " << Tries << endl;
            GameLoop = false;
        }
    }
    cout << "---------------------------------------------------" << endl;
    cout << " glad you enjoyed it  ---- bye! " << endl;
    return 0;
}