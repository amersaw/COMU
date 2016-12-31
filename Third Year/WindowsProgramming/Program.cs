using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    class Program
    {
        static void Main(string[] args)
        {
            Threadler.ThreadHavuzuIle();
            Threadler.ThreadNesnesiIle(); 
            Threadler.TaskIle();

            while (true)
            {
                Console.WriteLine("AA");
                System.Threading.Thread.Sleep(400);
            }
        }
    }
}
