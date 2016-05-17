#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <string>

using namespace std;
string Version = "V1.00.00";
string NameProgram = "Functions";

int Dice(int rolls = 1, int sides = 6)
{
	int result = 0;
	srand(time(NULL));
	for ( int loop =0; loop < rolls; loop = loop + 1)
	{
        	result += rand() % sides + 1;
	}
	return result;
}

int Distance(double oX0, double oY0, double tX1, double tY1)
{
    double result = 0;
    result = sqrt((tX1 - oX0)*(tX1 - oX0) + (tY1 - oY0)*(tY1 - oY0));
    return int(result);
}

int main()
{
    cout << "**** Starting run now ****" << endl;
    cout << NameProgram << " test driver "<< Version << endl;
    cout << "D10 one roll " << Dice(1,10) << endl;
    cout << "D6 rolls (one)" << Dice() << endl;
    cout << "D6 six rolls " << Dice(6,6)  << endl;
    cout << "Distance between 0,1 and 0,10 " << Distance(0,0,0,10) << endl;
    cout << "Distance between 1,0 and 1,10 " << Distance(1,0,1,10) << endl;
    cout << "Distance between 1,1 and 11,11 " << Distance(1,1,11,11) << endl;
    cout << "Distance between 0,1 and 0,-10 " << Distance(0,0,0,10) << endl;
    cout << "Distance between 1,0 and 1,-10 " << Distance(1,0,1,10) << endl;
    cout << "Distance between 1,1 and -11,-11 " << Distance(1,1,11,11) << endl;
    cout << "**** Ending run now ****" << endl;
    return 0;
}
