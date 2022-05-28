using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Switch
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Switch";

            int num = 3;
            string day;

            switch (num)
            {
                case 1: day = "Monday"; break;
                case 2: day = "Tuesday"; break;
                case 3: day = "Wednesday"; break;
                case 4: day = "Thursday"; break;
                case 5: day = "Friday"; break;
                default: day = "Weekend Day"; break;
            }

            Console.WriteLine("Day " + num + " : " + day);
            Console.ReadKey();
        }
    }
}
