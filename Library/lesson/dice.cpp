#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int main()
{
    srand(time(0));
    int d1, d2;
    for ( int i = 0; i < 6; i++ )
    {
        d1 = rand() % 20 + 1 ;
        d2 = rand() % 20 + 1 ;
        cout << "You rolled a " << d1 << " and a " << d2 << endl;
    }
    return 0;
}