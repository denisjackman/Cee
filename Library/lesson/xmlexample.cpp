#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

bool Test()
{
   XMLDocument doc;

   XMLError eResult = doc.LoadFile("../../files/example1.xml");
   if (eResult != XML_SUCCESS) return false;
   const char* hello = doc.FirstChildElement("Hello")->GetText();
   cout << hello << endl;

   return true;
}

int main()
{
   Test();
}