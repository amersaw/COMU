using System.Collections.Generic;

//Linq extension methodlari kullanabilmek icin bu namespace dahil edilmesi lazim
using System.Linq;

namespace SampleCodes
{
    class Linq
    {
        List<Person> People = new List<Person>()
        {
            new Person {Id = 1, Name = "Amer", LastName="Sawan" },
            new Person {Id = 2, Name = "Mehmet", LastName="BlaBla" },
            new Person {Id = 3, Name = "Blabla", LastName = "Foo" }
        };
        void MainKod()
        {
            //Linq sorgulamalari ya extension methodlari kullanarak yazilir
            var result = People.Where(p => p.Name == "Amer").Select(p=> p.Name);

            //Ya da from ... in ... where ... select ... syntaxi ile yazilir.
            var result2 = from p in People where p.Name == "Amer" select p.Name;

            //Yukarida iki yazilan sorgulamalar tam ayni iş yapıyorlar ama farklı bir syntax ile

            //Burası p tipini nedir ?
                //biz biliyoruz ki People : Person tipinden bir liste
                //bundan dolayı p Person tipindendir
            var rr = from p in People where p.Id == 2 select p.Name;

        }
    }
}
