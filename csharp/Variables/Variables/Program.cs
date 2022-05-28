using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Variables
{
    class Program
    {
        static void Main(string[] args)
        {
            char letter ;               // Declaring a Variables 
            letter = 'A' ;              // initialising the variable 
            int number ;                // declaring a variable 
            number = 100 ;              // initialising the variable 
            float body = 98.6f ;        // declaring and initialising a variable 
            double pi = 3.14159 ;       // declaring and initialising a variable 
            decimal sum = 1000.00m ;    // declaring and initialising a variable
            bool flag = false ;         // declaring and initialising a variable 
            string text = "C# is fun" ; // declaring and initialising a variable 

            Console.WriteLine("char letter:\t" + letter);
            Console.WriteLine("int number : \t" + number);
            Console.WriteLine("float body:\t" + body);
            Console.WriteLine("double pi:\t" + pi);
            Console.WriteLine("decimal sum:\t" + sum);
            Console.WriteLine("bool flag:\t"+flag);
            Console.WriteLine("String text:\t" + text);

            Console.ReadKey();
        }
    }
}
