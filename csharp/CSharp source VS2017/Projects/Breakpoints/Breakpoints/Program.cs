using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Breakpoints
{
    class Program
    {
        static void Main(string[] args)
        {
            int i, j, k;
            int pass = 0;

            for ( i = 1; i < 4; i++ )
            {
                for ( j = 1; j < 4; j ++ )
                {
                    for ( k = 1; k < 4; k++ )
                    {
                        pass++;
                    }
                }
            }
        }
    }
}
