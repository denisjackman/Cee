using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace input
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Input";
            Console.Write("Please Enter Your Name: ");
            string name = Console.ReadLine();
            Console.WriteLine("Welcome " + name + "!");
            Console.ReadKey();
        }
    }
}
