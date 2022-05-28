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

            Console.Write("Please Enter A Number: ");
            double num = Convert.ToDouble(Console.ReadLine());
            Console.Write("Now Enter Another Number: ");
            double sum = num + Convert.ToDouble(Console.ReadLine());

            Console.WriteLine("Total = " + sum);
            Console.ReadKey();
        }
    }
}
