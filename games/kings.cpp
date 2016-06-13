/*
Kings and Queens
This is an exercise in coding c++ plus conversion from zx81 to modern architecture
the original listing is taken from a Melbourne house books "ZX81 30 Programs"
Which was the center of my universe in 1978 (or so)
I have adjusted the code to a more modern style.

Author  :   Denis Jackman
Date    :   13th June 2016
Version :   1.00.00
Licence :   GPL 3
*/
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
/*
Kings and queens

knowledge of history. You will be asked who was reigning in a particular year, and
given three answers from which to select. You then type the number of the
answer, and the computer will tell you if you are right or not.

Program Structure

Initialize variables
FOR J=1 TO 3
    Select a date
    Find the king who reigned then
NEXT J
Select one of the 3 dates
Print question and choices
Check the answer
Run the program again

The kings and years of their death are stored in the string Z$. The entry
for each king is 7 characters long - padded with blanks if necessary. When
a date has been chosen, each entry is checked until one is found where the
king died after the chosen year.
  The next entry is obtained by adding 7 to the position of the character
that was previously being considered.
  B$ is a two-dimensional array used to store the names of the 3 kings
offered as choices. B$(1,1) refers to the first character in the first
name. B$(1) refers to the whole of that name.
  Note that the program is run again at the end. RUN does not clear the
screen, so the question remains on the screen while the computer selects
the next question. This gives you time to see the answer given by the
computer.
*/

/*
100 LET Z$="1087W1 1100W2 1135H1 1154ST 1189H2 1199R1 1216J  1272H3 1307ED11327ED21377ED31399R2 1413H4 1422H5 1461H6 "
110 DIM P(3)
120 DIM B$(3,3)
130 RAND
140 FOR J=1 TO 3
150 LET P(J)=INT(RND*396+1065)
160 LET X$="0000"
170 LET I=J/J
180 LET X$=Z$(I TO I+3)
190 LET I=I+7
200 IF VAL(X$)<=P(J) THEN GOTO 180
210 LET B$(J)=Z$(I-3 TO I-1)
220 NEXT J
230 LET N=INT(RND*3+J/J)
240 CLS
250 PRINT "WHO REIGNED IN ";P(N),"1 ";B$(J/J);"  2 ";B$(2);"  3 ";B$(3)
260 INPUT X
270 IF B$(X)=B$(N) THEN PRINT "YES"
280 IF B$(X)<>B$(N) THEN PRINT "NO ";B$(N)
290 RUN
*/

/*
Take especial care in entering line 100! Remember the format we are using:
for each monarch, we enter the date of his death, then a three letter code
for the monarch's name. Each entry therefore has 7 characters. (Where the
abbreviation is less than 3 characters, we make it up to three by adding
spaces.)

Running the Program

This program will keep on running forever unless you [press] (BREAK) or
input an illegal value. You will be asked who reigned in a particular
year, and three possible answers will be given.
  It is possible that not all of these answers will be different. You will
still be marked correctly, no matter which of the correct answers you
choose. If the king died in the given year (so that there were 2 kings in
that year) choose the new king.
  If you select the wrong answer, the correct answer will be printed on
the screen.
*/

void ClearScreen()
{
    /*
    This will clear the screen
    */
    cout << "\033[2J\033[1;1H";
}

int main(int argc, char *argv[])
{
    /* 100 */
    int Reigns[] = {1066,1087,1100,1135,1154,1189,1199,1216,1272,1307,1327,1377,1399,1413,1422,1461,1470};
    string Royal[] = {"William I", "William II","Henry I","Stephen","Henry II","Richard I","John","Henry III","Edward I","Edward II","Edward III","Richard II","Henry IV","Henry V","Henry VI","Henry VI"};
    int CompGuess[3] = {0,0,0}; /*110 */
    string CompAnswer[3] = {"","",""};
    string CompDetail[3] = {"","",""};
    int Question = 0;
    int Lives = 0;
    bool GameLoop = true;
    bool GuessLoop = true;
    int PlayLoop = 0;
    int Score = 0 ;
    string PlayerAnswer = "";
    srand(time(0)); /* 130 */
    for ( int guessloop = 1; guessloop < 4; guessloop++ ) /* 140 - 220 */
    {
        CompGuess[guessloop] = rand() % 396 + 1067; /* 150 */
        for ( int loop = 0; loop < 17; loop++ )
        {
            if (Reigns[loop] > CompGuess[guessloop])
            {
                CompAnswer[guessloop] = Royal[loop - 1 ];
                CompDetail[guessloop] = Royal[loop -1 ] + " reigned from " + to_string(Reigns[loop -1 ]) + " to " + to_string(Reigns[loop]);
                break;
            }
            else if (Reigns[loop] == CompGuess[guessloop])
            {
                CompAnswer[guessloop] = Royal[loop - 1 ];
                CompDetail[guessloop] = Royal[loop]  + " reigned from " + to_string(Reigns[loop - 1 ]) + " to  " + to_string(Reigns[loop]);
                break;
            }
        }
    }
    while (GameLoop)
    {
        Score =0;
        Lives=10;
        PlayLoop = 1;
        GuessLoop = true;
        ClearScreen();
        cout << "I will ask you three questions " << endl;
        cout << "You have 10 chances to guess it " << endl;
        cout << "Good Luck!" << endl;

        while (GuessLoop)
        {
            cout << "You have " << Lives << " guesses remaining " << endl;
            cout << "Who reigned in " << CompGuess[PlayLoop] << "?"<< endl;
            getline(cin, PlayerAnswer);
            if (PlayerAnswer==CompAnswer[PlayLoop])
            {
                cout << "Well Done ! "<< endl;
                cout << CompDetail[PlayLoop] << endl;
                Score++;
                PlayLoop ++;
            }
            Lives = Lives - 1;
            if (PlayLoop > 3)
            {
                GuessLoop = false;
            }
            if (Lives == 0)
            {
                GuessLoop = false;
            }
        }
        cout << "your score was "<< Score << " and you used " << 10 -  Lives<< " guesses" << endl;
        cout << "do you wish to play again ? (y/n)" << endl;
        cin >> PlayerAnswer;
        if (PlayerAnswer=="n")
        {
            GameLoop = false;
        }
    }

}