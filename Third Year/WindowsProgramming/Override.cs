using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    class Kisi
    {
        public string Name { get; set; }
        public string TCNo { get; set; }
        public virtual string BilgilerAl()
        {
            return "TC:" + TCNo + "Ad:" + Name;
        }
    }

    class Ogrenci : Kisi
    {
        public string Bolum { get; set; }


        public override string BilgilerAl()
        {
            return "TC:" + TCNo + ", Ad:" + Name + ", Bolum:" + Bolum;
        }
    }
}
