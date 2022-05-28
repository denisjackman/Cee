using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Parts
{
    public partial class Sailboat
    {
        private string make;
        private string model;

        public Sailboat(string make, string model)
        {
            this.make = make;
            this.model = model;
        }
    }
}
