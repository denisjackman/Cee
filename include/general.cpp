#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

bool gDebugMode = false;
string gDebugLogFileLocation = "debug.log";
ofstream gDebugLogFile;

void DebugModeInitialise()
{
    if (gDebugMode)
    {
        gDebugLogFile.open(gDebugLogFileLocation);
    }
}

void DebugModeTerminate()
{
    if (gDebugMode)
    {
        gDebugLogFile.close();
    }
}

void Print(string OutputString)
{
    if (gDebugMode)
    {
        gDebugLogFile << OutputString << endl;
    }
    cout << OutputString << endl;
}