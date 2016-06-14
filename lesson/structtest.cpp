#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct customcolour
{
    int red;
    int green;
    int blue;
};

int main(int argc, char *argv[])
{
    string line;
    string name;
    string rgbcode;
    string redcode;
    string greencode;
    string bluecode;
    string stuff;
    string morestuff;

    ifstream myfile ("../files/colours.csv");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            name = line.substr(1,line.find(",")-1);
            rgbcode = line.substr(line.find(",")+1);
            redcode = rgbcode.substr(1,rgbcode.find("-"-1));
            stuff = rgbcode.substr(rgbcode.find("-")+1);
            greencode  = rgbcode.substr(rgbcode.find("-")+1);
            morestuff = stuff.substr(stuff.find("-")+1);
            bluecode  = morestuff.substr(morestuff.find("-")+1);

            cout << name << " & " << redcode << " : " << greencode << " : " << bluecode <<  endl;
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}