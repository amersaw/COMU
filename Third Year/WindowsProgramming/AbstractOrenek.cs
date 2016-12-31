using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    abstract class AbstractOrenek
    {
        public abstract void DoIt();
        public virtual void DDD()
        {

        }
    }
    class Ornek2 : AbstractOrenek
    {
        public virtual void adf()
        {

        }
        public override void DoIt()
        {
            throw new NotImplementedException();
        }
    }
    class ornek3 : Ornek2
    {

    }
}
