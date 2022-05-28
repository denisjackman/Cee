using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Debug
{
    class Program
    {
        static void Main(string[] args)
        {
            int pass = 0;
            int unit = 2;

            for (int i = 1; i < 3; i++)
            {
                pass = (pass + 1);
                unit = square(unit);
            }
        }

        static int square(int num)
        {
            return (num * num);
        }
    }
}
