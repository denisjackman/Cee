#include <iostream>
using namespace std;

int main()
{
    enum Color {    red,
                    green,
                    blue,
                    purple,
                    white,
                    black  };
    Color r = red;
    r = black;
    switch(r)
    {
        case red  :
        {
            cout << "red" << endl;
            break;
        }
        case green:
        {
            cout << "green" << endl;
            break;
        }
        case blue :
        {
            cout << "blue" << endl;
            break;
        }
        case purple:
        {
            cout << "purple" << endl;
            break;
        }
        case white:
        {
            cout << "white" << endl;
            break;
        }
        case black:
        {
            cout << "black" << endl;
            break;
        }
    }
}