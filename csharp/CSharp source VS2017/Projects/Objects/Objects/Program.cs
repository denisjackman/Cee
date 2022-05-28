using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Objects
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Objects";

            Dog fido = new Dog();
            fido.setValues("Fido", 3, "Brown");

            string tagF = String.Format("{0} is a {1} year old {2} dog",
                fido.getName(),
                fido.getAge(),
                fido.getColor()
            );
            Console.WriteLine(tagF + fido.bark());

            Dog lucy = new Dog();
            lucy.setValues("Lucy", 2, "Gray");

            string tagL = String.Format("{0} is a {1} year old {2} dog",
                lucy.getName(),
                lucy.getAge(),
                lucy.getColor()
            );
            Console.WriteLine(tagL + lucy.bark());

            Console.ReadKey();
        }
    }

    public class Dog
    {
        private string name, color;
        private int age;

        public void setValues(string name, int age, string color)
        {
            this.name = name;
            this.age = age;
            this.color = color;
        }

        public string getName() { return name; }
        public int getAge() { return age; }
        public string getColor() { return color; }

        public string bark() { return "\nWoof, woof!\n"; }
    }
}
