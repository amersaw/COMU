using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    class Eventler
    {
        delegate void BirSeyOlma(string detayler);

        event BirSeyOlma Basladi;
        event BirSeyOlma Bitti;

        public static void EkreneYaz(string d)
        {
            Console.WriteLine("Basladi:" + d);
        }
        public static void EmailGonder(string d)
        {
            //Email gönderme işlemleri
        }

        public void MainKod()
        {
            //bu fonksiyon ekledikten sonra artık "başladi" eventi canladırdığında 
            //eklenilen fonksiyonlar çağırılacak.
            //bu durumda hem ekrene yazılacak hem de email gönderilecek
            Basladi += EkreneYaz;
            Basladi += EmailGonder;

        }


    }
}
