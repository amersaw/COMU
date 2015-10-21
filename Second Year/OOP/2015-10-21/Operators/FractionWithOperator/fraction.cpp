// fraction.cpp
// Definition of fraction class

#include<iostream>
#include"fraction.h"
using namespace std;

Fraction::Fraction(int num, int denom)    // CONSTRUCTOR
{
	numerator=num;
	if (denom==0) denominator=1;
	else denominator=denom;
		 cout << "Constructor of Fraction" << endl;
}

void Fraction ::print() const
{
	cout << numerator << "/" << denominator << endl;
}
Fraction::Fraction(){
}
Fraction Fraction::operator+(const Fraction f) const{
    Fraction retval;
    retval.denominator = denominator * f.denominator;
    retval.numerator = numerator*f.denominator + f.numerator*denominator;
    return retval;
}
