// complex.cpp
//	Objetcs as a members of other classes 

#include<iostream>
#include"fraction.h"
#include"complex.h"
using namespace std;


// Constructor
// first, constructors of the member objects must be called
ComplexFrac::ComplexFrac(int re_in,int im_in):re(re_in,1),im(im_in,1)
{
		cout << "Constructor of ComplexFrac" << endl;
}

// Prints complex numbers on the screen
// print function of the member objects are called
void ComplexFrac::print() const
{
   re.print();  
   im.print();  
}
