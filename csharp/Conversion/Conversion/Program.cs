using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Conversion
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Conversion";
            Console.Write("Please Enter a Number: ");
            double num = Convert.ToDouble(Console.ReadLine());
            Console.Write("Now Enter another Number: ");
            double sum = num + Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Total = " + sum);
            Console.ReadKey();

        }
    }
}
