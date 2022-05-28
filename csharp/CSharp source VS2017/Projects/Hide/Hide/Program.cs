using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hide
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "Hide";

            Man henry = new Man();

            Hombre enrique = new Hombre();

            henry.speak();
            henry.speak("It's a beautiful evening");

            enrique.speak("Hola...");

            ((Man)enrique).speak("Es una tarde hermosa");

            Console.ReadKey();
        }
    }

    public class Man
    {
        public void speak()
        {
            Console.Write("Hello: ");
        }

        public void speak(string message)
        {
            Console.WriteLine(message + "!\n");
        }
    }

    public class Hombre : Man
    {
        public new void speak(string message)
        {
            base.speak();
            Console.WriteLine(message);
        }
    }
}
