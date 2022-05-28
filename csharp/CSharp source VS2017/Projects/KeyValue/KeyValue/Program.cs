using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KeyValue
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "KeyValue";

            Dictionary<string, string> BookList = new Dictionary<string, string>();
            BookList.Add("Stuart Yarnold", "Arduino");
            BookList.Add("Nick Vandome", "Windows 10");
            BookList.Add("Mike McGrath", "Java");

            Console.WriteLine("Popular Titles...");

            foreach (KeyValuePair<string, string> book in BookList)
            {
                Console.WriteLine("Key: " + book.Key + "\tValue: " + book.Value + " in easy steps");
            }
            Console.ReadKey();
        }
    }
}
