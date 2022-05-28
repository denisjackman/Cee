using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace AppendText
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "AppendText";

            string path = "C:\\Users\\Mike_\\Desktop\\oscar.txt";
            string[] poem = new string[]
            {
                "\tIn Debtors' Yard the stones are hard",
                "\tAnd the dripping wall is high",
            };
            string attrib = "\r\n\tThe Ballad Of Reading Gaol ";
            attrib += "(Oscar Wilde 1898)";

            if (File.Exists(path))
            {
                File.AppendAllText(path, attrib);
                Console.WriteLine("Appended To File: " + path);
            }
            else
            {
                try
                {
                    File.WriteAllLines(path, poem);
                    Console.WriteLine("File Written: " + path);
                }
                catch (Exception error)
                {
                    Console.WriteLine(error.Message);
                }
            }
            Console.ReadKey();
        }
    }
}
