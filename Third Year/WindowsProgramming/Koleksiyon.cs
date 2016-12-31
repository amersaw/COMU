
//Koleksiyonlarin namespace'i
using System.Collections;

//Koleksiyonlarin şablon tipin naespace'i
using System.Collections.Generic;

namespace SampleCodes
{
    class Koleksiyon
    {
        public static void MainKod()
        {

            //Koleksiyonlar genel halinde
            {
                Queue q = new Queue();
                Stack s = new Stack();
            }


            //Koleksiyonların şablon halinde
            {
                Queue<int> q = new Queue<int>();
                Stack<int> s = new Stack<int>();
            }
        }
    }
}
