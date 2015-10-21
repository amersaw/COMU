#include <iostream>

using namespace std;


class ComplexT{
    double re,im;
public:
    ComplexT operator+(const ComplexT&) const;
    ComplexT operator-(const ComplexT&) const;
    void print();
    ComplexT(); //constructor with no arguments
    ComplexT(double,double);
};

ComplexT::ComplexT(double r,double i){
        re=r;
        im=i;
    }



ComplexT::ComplexT(){
        re=0;
        im=0;
    }


ComplexT ComplexT::operator+(const ComplexT& z)const{
    cout<<"Operator + is called"<<endl;
    double new_re, new_im;
    new_re = re + z.re;
    new_im = im + z.im;
    return ComplexT(new_re,new_im);
}

ComplexT ComplexT::operator-(const ComplexT& z)const{
    cout<<"Operator - is called"<<endl;
    double new_re, new_im;
    new_re = re - z.re;
    new_im = im - z.im;
    return ComplexT(new_re,new_im);
}

void ComplexT::print(){
    cout<<"Real : "<<re<<"\tImaginary : "<<im<<endl;
}

int main()
{
    ComplexT z1(1,2), z2(3,2),z3;

    (z1+z2).print();
    (z1-z2).print();

    return 0;
}
