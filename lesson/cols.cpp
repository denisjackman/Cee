#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    // https://en.wikipedia.org/wiki/ANSI_escape_code#graphics
    string line ="";
    string precode = "\033[";
    string codes = "1;5;47;31";
    string postcode = "m";
    string aftercode = "\033[0m";
    cout << precode << codes << postcode << "bold red text"<< aftercode << endl;
}