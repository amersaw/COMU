using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    class Delegates
    {
        //tanimlarken bir fonksyon tanimlaniyormuşuz gibi ama başında delegate yazıyoruz
        //buna bir fonksiyona işaret edebilmek için o fonksiyon aynı imza olması lazım yani:
        //   iki parametre alıyor ve bu parametreler :
        //         1- int
        //         2- int
        //   int tipinden döndürüyor
        delegate int Islem(int a, int b);


        public static int Toplama(int x, int y)
        {
            return x + y;
        }
        public static int Carpma(int x, int y)
        {
            return x - y;
        }

        public static double bolme(int x, int y)
        {
            return x / y;
        }

        public static void MainKod()
        {
            Islem toplamaIslemi = new Islem(Toplama);
            Islem carpmaIslemi = new Islem(Carpma);

            //HATALI : cunku bolme fonksiyonu ayni imza degildir (double tipinden döndürüyor)
            //Islem bolmeIslemi = new Islem(bolme);

            int sonuc;

            
            //çağırırken ise sanki o fonksiyonu çağırıyormuşuz gibi (delegate üzerinde)
            sonuc = toplamaIslemi(1, 2);
            sonuc = carpmaIslemi(4, 4);

        }
    }
}
