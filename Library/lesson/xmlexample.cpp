#include <iostream>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

bool Test1();
bool Test2();
bool Test3();
bool Test4();
bool Test5();

int main()
{
   //Test1();
   //Test2();
   //Test3();
   //Test4();
   Test5();
}

bool Test1()
{
   // This reads an XML document
   XMLDocument doc;

   XMLError eResult = doc.LoadFile("../../files/xml/example1.xml");
   if (eResult != XML_SUCCESS) return false;
   const char* hello = doc.FirstChildElement("Hello")->GetText();
   cout << hello << endl;

   return true;
}

bool Test2()
{
   // This reads an XML document
   XMLDocument doc;

   XMLError eResult = doc.LoadFile("../../files/xml/example2.xml");
   if (eResult != XML_SUCCESS) return false;
   const char* hello = doc.FirstChildElement("poetry")->FirstChildElement("verse")->GetText();
   cout << hello << endl;

   return true;
}

bool Test3()
{
   // This reads an XML document
   XMLDocument doc;

   XMLError eResult = doc.LoadFile("../../files/xml/example3.xml");
   if (eResult != XML_SUCCESS) return false;

   const char* hello = doc.FirstChildElement("shapes")->FirstChildElement("circle")->Attribute("name");
   cout << hello << endl;
    return true;
}

bool Test4()
{
   // This reads an XML document
   XMLDocument doc;
   XMLError eResult = doc.LoadFile("../../files/xml/example4.xml");
   if (eResult != XML_SUCCESS)
   {
        return false;
   }
   const char* hello = doc.FirstChildElement("MyApp")->FirstChildElement("Messages")->FirstChildElement("Welcome")->GetText();
   const char* farewell = doc.FirstChildElement("MyApp")->FirstChildElement("Messages")->FirstChildElement("Farewell")->GetText();
   const char* info = doc.FirstChildElement("MyApp")->FirstChildElement("Windows")->FirstChildElement("Window")->Attribute("name");
   cout << hello << " : " << farewell << " : " << info <<  endl;
   return true;
}

bool Test5()
{
    // This reads an XML document and iterates through the child elements of the
    XMLDocument doc;
    XMLError eResult = doc.LoadFile("../../files/xml/books.xml");
    if (eResult != XML_SUCCESS)
    {
        return false;
    }
    XMLElement *levelElement = doc.FirstChildElement("catalog");
    for (XMLElement* child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
        // do something with each child element
        cout << child->Attribute("id") << " : " ;
        cout << child->FirstChildElement("genre")->GetText() << " : ";
        cout << child->FirstChildElement("title")->GetText() << " (";
        cout << child->FirstChildElement("author")->GetText() << ")";
        cout << endl;
    }
    return true;
}