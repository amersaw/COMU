#include <iostream>

using namespace std;


class ComplexT{
    double re,im;
public:
    void operator() (int);  //Bir parametre alan fonksiyon operatoru prototipi
    void operator() ();     //Parametresiz fonksiyon operatoru prototipi

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

void ComplexT::operator()(int i){
    if(i == 1){
        cout<<"Real Part : "<<re<<endl;
    } else if (i==2){
        cout<<"Imaginary Part : "<<im<<endl;
    } else{
        cout<<"Invalid Argument"<<endl;
    }
}
void ComplexT::operator()(){
    cout<<"Real : "<<re<<"\tImaginary : "<<im<<endl;
}


int main()
{
    ComplexT z1(1,2), z2(3,2),z3;

    z1();
    z2();

    return 0;
}
