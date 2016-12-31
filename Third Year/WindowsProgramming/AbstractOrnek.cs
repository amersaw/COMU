using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    abstract class AbstractOrnek
    {
        //abstract class olduğu için abstract methodlar yazabiliriz
        public abstract void DoIt();

        //abstract class içerisinde virtual methodları da yazabilirz
        //içerisinde kodlar var olması lazım ama
        //bu class'tan miras alan claslar, bu methodu yenide yazabiliyorlar override ile
        public virtual void DDD()
        {

        }
    }

    //Ornek2 class AbstractOrnek class içindeki butun şeyler vardır
    //içerisinde abstract methodlar varsa, bunları burda tanımlamaız zorundayız (
    class Ornek2 : AbstractOrnek
    {
        public override void DoIt()
        {
            throw new NotImplementedException();
        }

        public void EkMethod()
        {

        }

        //HATALI:bu class abstract olmadığı için, içinde abstract methodlar yazamayiz
        abstract void AbstractMethodOrnek()
        {

        }
    }
}
