using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleCodes
{
    class TryCatchFinally
    {
        void MainKod()
        {
            try
            {
                string s = "abc";

                //burda bir FormatException firlatilacak
                int i = Convert.ToInt32(s);
                
            }
            //bu exception burda yakalanılmayacak
            catch (IndexOutOfRangeException)
            {

            }
            //Bu exception burda yakalanılacak
            catch (FormatException)
            {

            }
            finally
            {
                //Try icindeki kodu caliştırdıktan sonra hata olsa hata olmazsa 
                //burdaki yazilan kodlarçalıştırılacak.
            }
        }
    }
}
