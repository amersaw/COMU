using System.Collections;
namespace SampleCodes
{
    //Bu class şablon tipi sayılır, çünkü tanımlarken ona T tipi ne olduğunu söyleriz 
    class Sablonlar<T>
    {
        //bize virilen T tipi artik tanimlanmis bir tip gibi kullaniyoruz
        //Bu fonksiyonun döndürme tipi T
        public T VarsayilanDegerDondur()
        {
            //HATALI: yapamıyoruz çünkü T tipi int olabilir ve null int'e çevirilmez
            //return null;

            //HATALI: bunu da yapamıyoruz, çünkü T tipi herhangi class olabilir
            //Person tipinden ise 0 Person'a çevirlimez 
            //return 0;
            //EEEH "T" tipinin varsayılan değeri nasıl alabiliriz 
            //"default" kullanarak, int ise 0, refereance tiplerden ise null, bool ise false...vb
            return default(T);
        }
    }

    //virilen T tipi class olmasi gerekiyordur. ornek int olamaz
    class SablonTürüKısıtmalarla1<T> where T : class { }

    //virilen T tipi IEnumerable interface'i tanimlanmiş olması lazım
    class SablonTürüKısıtmalarla2<T> where T : IEnumerable { }


}
