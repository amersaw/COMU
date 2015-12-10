#include <iostream>
using namespace std;

class ComplexT{								//A class to define complex numbers 
    float re,im;
  public:
  	 ComplexT(float r , float i):re(r),im(i){}  // Constructor
     bool operator>(const ComplexT&) const;     // header of operator> function
      bool operator==(const ComplexT&) const; 
	 float get_re()const {return re;}
	 float get_im()const {return im;}
	 friend ostream& operator <<(ostream&, const ComplexT&);
};

// The Body of the function for operator > 
bool ComplexT::operator>(const ComplexT& z) const
{
   float f1 = re * re + im * im;
   float f2 = z.re * z.re + z.im * z.im;
   return f1 > f2;
}

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

// template function  
template <class type> 
const type & MAX(const type &v1, const type & v2) 
{ 
    if (v1 > v2) return v1;
       else      return v2;
} 

int main()
{
   int i1=5, i2= -3;
   char c1=90, c2='N',c3;
   c3=c1+c2;
   cout << c3 << endl;
   float f1=3.05, f2=12.47;
   ComplexT z1(1.4,0.6), z2(4.6,-3.8);
   cout << MAX(i1,i2) << endl;
   cout << MAX(c1,c2) << endl;
   cout << MAX(f1,f2) << endl;
   cout << MAX(z1,z2) << endl;
   cout << "z1 ile z2 eþitmidir? " << (z1==z2) << endl;
   system("pause");
	return 0;
}
