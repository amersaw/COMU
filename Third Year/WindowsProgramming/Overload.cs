using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    static class Overload
    {
        public static void IsYap(int a, int b)
        {
            Console.WriteLine("a:" + a + ",b:" + b);
        }

        //Burası overload yaptık, IsYap methodu 2 farklı şekilde çağırabilirz artık:
            //ya 2 parametre ile
            //yada 3 parametre ile
        public static int IsYap(int a, int b, int c)
        {
            return a + b - c + 978;
        }

        //HATALI:boyle overload yapamiyoruz, çünkü önceki method ve bu method 
        //ikisini 2 tane int parametre alıyorlar
        //geri dönüş fark var da, am overload için fark yok
        public static int IsYap(int a, int b)
        {
            return a + b - 5;
        }
        
        //onu yapabilmek için kesin farklı bir isim kulanmamız lazım.
        public static int IsYap2(int a, int b)
        {
            return a + b - 5;
        }



    }
}
