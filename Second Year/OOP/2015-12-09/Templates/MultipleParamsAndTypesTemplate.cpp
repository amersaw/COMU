#include <iostream>
using namespace std;
class ComplexT{								//A class to define complex numbers 
    float re,im;
  public:
  	 ComplexT(float r , float i):re(r),im(i){}  // Constructor
     bool operator==(const ComplexT&) const; 
	 float get_re()const {return re;}
	 float get_im()const {return im;}
	 friend ostream& operator <<(ostream&, const ComplexT&);
};

bool ComplexT::operator==(const ComplexT& z) const
{
   float f1 = re * re + im * im;
   float f2 = z.re * z.re + z.im * z.im;
   return f1 == f2;
}

// Overloading <<
ostream& operator <<(ostream& out, const ComplexT& z)  
{
	out << "( " << z.re << " , " << z.im << " )" << endl;
   return out;
};



template <class atype, class btype>
btype find(const atype* array, atype value, btype size){
      for(btype i=0; i<size; i++)
          if (array[i]==value) return i;
      return static_cast<btype>(-1);
}

char chrArr[]={'s','r','g','y','h','v','q2'};
char ch='h';
int intArr[]={3,5,16,14,26,13,21,22};
int in=13;
double duArr[]={1.0,3.2,4.2,-1.4,6.7};
double db=4.2;
ComplexT z1(10,20);
ComplexT z[]={z1,ComplexT(20,10),ComplexT(33,21),ComplexT(32,10)};

int main(){
	cout << "\n 'h' in chrArr: index="<< find(chrArr, ch, 7)<<endl;
	cout << "\n 13 in chrArr: index=" << find(intArr, in, 8)<<endl;
	cout << "\n 4.2 in chrArr: index="<< find(duArr, db, 5)<<endl;
	cout << "\n ComplexT(10,20) in chrArr: index=" << find(z, ComplexT(33,21), 4)<<endl;
	system ("Pause");
    return 0;
}
