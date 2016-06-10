//Michael Barker
//Program that rolls 2 dice

#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

class dice_roll
{
public:
    int roll_di (int& a)
    {
        int x;
        srand(time(0));
        x = rand();
        a = (x%6) + 1;
        return a;
      }
};


int main()
{
    int d1, d2;
    dice_roll rollin;
    for ( int i = 0; i < 6; i++ )
    {
        d1 = rollin.roll_di(d1);
        d2 = rollin.roll_di(d2);
        cout << "You rolled a " << d1 << " " << d2 << endl;
    }
    return 0;
}