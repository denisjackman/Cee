#include <iostream>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

using namespace std;
using namespace boost;


int DiceRoll(int Rolls = 1, int Sides = 6)
{
    int result = 0;
    return result;
}


int main()
{

    int Rolls = 12;
    int Sides = 6;

    typedef mt19937 RNGType;
    RNGType rng( time(0) );
    uniform_int<> one_to_six( 1, Sides );
    variate_generator< RNGType, uniform_int<> > dice(rng, one_to_six);
    for ( int i = 0; i < Rolls; i++ )
    {
        int n  = dice();
        cout << n << endl;
    }
}

/*
g++ boost.cpp -w -o boost
*/