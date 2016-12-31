using System;
using System.Threading;
using System.Threading.Tasks;

namespace SampleCodes
{
    class Threadler
    {
        public static void ThreadHavuzuIle()
        {
            ThreadPool.QueueUserWorkItem(ArkaPlandaKodlar);
        }
        public static void ThreadNesnesiIle()
        {
            Thread t = new Thread(ArkaPlandaKodlar);
            t.Start();
        }

        public static void TaskIle()
        {
            Task t = new Task(() => { ArkaPlandaKodlar(null); });
            t.Start();
        }


        static void ArkaPlandaKodlar(object parametreler)
        {

            while (true)
            {
                System.Console.WriteLine(DateTime.Now);
                System.Threading.Thread.Sleep(1000);
            }
        }
    }

}
