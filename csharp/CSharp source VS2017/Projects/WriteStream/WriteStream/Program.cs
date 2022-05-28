using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace WriteStream
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "WriteStream";

            string path = "C:\\Users\\Mike_\\Desktop\\robert.txt";
            string[] poem = new string[]
            {
                "\tThis truth finds honest Tam o' Shanter" ,
                "\tAs he from Ayr one night did canter" ,
                "\tOld Ayr, which never a town surpasses",
                "\tFor honest men and bonny lasses."
            };
            string attrib = "\r\n\tTam O'Shanter (Robert Burns 1790)";

            try
            {
                using (StreamWriter writer = new StreamWriter(path))
                {
                    foreach (string line in poem)
                    { writer.WriteLine(line); }
                }

                using (StreamWriter writer = new StreamWriter(path, true))
                {
                    writer.WriteLine(attrib);
                    Console.WriteLine("File Written: " + path);
                }
            }
            catch (Exception e) { Console.WriteLine(e.Message); }
            Console.ReadKey();
        }
    }
}
