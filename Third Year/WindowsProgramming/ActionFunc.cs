using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    class ActionFunc
    {
        int Kare(int s)
        {
            return s * s;
        }

        void SayiYaz(double s)
        {
            Console.WriteLine(s.ToString(););
        }
        void Main()
        {

            //delegate int df(int x);
            //df artık tam Func<int,int> gibidir

            //delegate void da(double d);
            //da artıkt tam Action<double> gibidir



            //bir tane int parametre alan ve int tipinden donduren
            Func<int, int> a = new Func<int, int>(Kare);
            
            //1 double parametre alan ;
            Action<double> yazdiran = new Action<double>(SayiYaz);
        }


    }
}
