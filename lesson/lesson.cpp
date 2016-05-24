#include <string>
#include <iostream>
#include "../include/gamefunction.h"

using namespace std;

void ClearScreen()
{
    /*
    This will clear the screen
    */
    cout << "\033[2J\033[1;1H";
}

void GuessGame()
{
    ClearScreen();
    cout << "---------------------------------------------------" << endl;
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
        cout << "---------------------------------------------------" << endl;
    }
    cout << "---------------------------------------------------" << endl;
    cout << "glad you enjoyed it  ---- bye! " << endl;
    cout << "---------------------------------------------------" << endl;
}

void RockPaperScissor()
{
    ClearScreen();
    cout << "---------------------------------------------------" << endl;
    cout << "Welcome to the Rock,Paper,Scissors game " << endl;
    cout << "Good Luck " << endl;
    cout << "---------------------------------------------------" << endl;
    int Tries = 0;
    bool GameLoop = true;
    int ComputerAnswer = 0;
    int UserAnswer = 0;
    int UserScore = 0 ;
    int ComputerScore = 0;
    while (GameLoop)
    {
        Tries += 1;
        ComputerAnswer = DiceRoll(1,3);
        cout << "Turn ("<< Tries << ") Score ("<< UserScore <<")"<<endl;
        cout << "Choose a strategy please  " << endl;
        cout << " (1) Rock " << endl;
        cout << " (2) Paper " << endl;
        cout << " (3) Scissors " << endl;
        cout << " (4) Exit " << endl;
        cin >> UserAnswer;
        cout << "You choose (" << UserAnswer << ") - I choose (" << ComputerAnswer << ") " << endl;

        if (UserAnswer == 4)
        {
            cout << "Thanks for playing " << endl;
            GameLoop = false;
        }
        else if (UserAnswer==ComputerAnswer)
        {
            cout << "Draw! " << endl;
        }
        else if ((UserAnswer == 1) and (ComputerAnswer == 3))
        {
            cout << "You win !" << endl;
            UserScore += 1 ;
        }
        else if ((UserAnswer == 2) and (ComputerAnswer == 1))
        {
            cout << "You win !" << endl;
            UserScore += 1 ;
        }
        else if ((UserAnswer == 3) and (ComputerAnswer == 2))
        {
            cout << "You win !" << endl;
            UserScore += 1 ;
        }
        else
        {
            cout << "You Lose !" << endl;
        }
    }

}


int main (int argc, char* args[] )
{
    cout << "---------------------------------------------------" << endl;
    cout << "Welcome to the Game player "<< endl;
    cout << "---------------------------------------------------" << endl;

    bool PlayLoop = true;
    while (PlayLoop)
    {
        int ChooseGame = 0;
        cout << "Choose a game to play " << endl;
        cout << "    (1) Guess the Number " << endl;
        cout << "    (2) Rock Paper Scissor " << endl;
        cout << "    (3) Insult " << endl;
        cout << "    (0) Exit " << endl;
        cout << "Please choose : ";
        cin >> ChooseGame;
        switch(ChooseGame)
        {
            case 1:
                GuessGame();
                break;
            case 2:
                RockPaperScissor();
                break;
            case 3:
                cout << InsultGenerator() << endl;
                break;
            case 0:
                ClearScreen();
                cout << "Thanks for playing " << endl;
                PlayLoop = false;
                break;
            default:
                cout << "Really you cannot choose ? " << endl;
        }
    }
    return 0;
}