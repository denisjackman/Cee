using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Parts
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Parts";

            Sailboat boat = new Sailboat("Laser", "Classic");

            boat.describe();

            Console.ReadKey();

        }
    }

    public partial class Sailboat
    {
        public void describe()
        {
            Console.WriteLine("Sailboat: {0} {1}", make, model);
        }
    }
}
