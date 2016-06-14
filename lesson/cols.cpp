#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    // https://en.wikipedia.org/wiki/ANSI_escape_code#graphics
    string line ="";

    //ansi codes
    string precode = "\033[";
    string blink = "5";
    string bold = "1";
    string foregroundcolour = "4";
    string textcolour = "3";
    string postcode = "m";
    string aftercode = "\033[0m";

    //ansi colour list
    string black = "0";
    string red = "1";
    string green = "2";
    string yellow = "3";
    string blue = "4";
    string magenta = "5";
    string cyan = "6";
    string white = "7";

    // construct the text string
    string codes = bold +";"+ blink +";"+ foregroundcolour + white +";"+ textcolour + red ;

    // display
    cout << precode << codes << postcode << "bold red text"<< aftercode << endl;
}