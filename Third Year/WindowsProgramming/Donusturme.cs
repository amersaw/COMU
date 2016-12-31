using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    class Donusturme
    {
        void Main()
        {
            /////////////////////////IMPLICIT////////////////////////////
            int a = 55;

            //buyuk tipten küçük tipe çevirmek istiyorsak, açık bir şekilde yazmamız lazım
            //burda sıkıntı yok, çünkü eminiz a'daki değer byte'te sığabilecek bir değer
            //255'ten daha büyük olsaydı, çalışma zamanında bir hata verecek
            byte b = (byte)a;



            /////////////////////////EXPLICIT////////////////////////////
            byte bb = 255;
            //Burasi dönüştürme yapıyoruz, ama söylemeden kabul edildi.
            //çünkü burası hiç bir zamanda hata olamaz.
            //bb'deki değer ne kadar büyük olursa (maksimum 255), int'te sığacaktır
            int aa = bb;

            //İmplicit gibi yazarsak ta sıkıntı yok
            int aaa = (int)bb;




            /////////////Örnekler
            double dd = 5.44;
            //HATALI: çünkü double'den int'e dönüştürme explisit, yani açık söylenmesi lazım
            //ve bilerek bu işlem yapıyoruz çünkü noktadan sonraki kısmı kayıp olacak.
            int ii = dd;


            //illaki istiyoruz bunun yapması, şöyle yaparız :
            ii = (int)dd;
            //^^^^^^^^^^^^^^^^^^^^^^
            //Bu demek ben dd'deki ondalik kısmı kayip olacağını kabul ediyorum 
            //ve razıyım ve bilerek yapıyorum




        }
    }
}
