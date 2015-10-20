// complex.h
// Decleration of complex numbers

#ifndef _complex_           // to include only once
#define _complex_

#include "fraction.h"       // decleration of Fraction is necesary

class ComplexFrac{			//  Complex numbers: has two fractions
	Fraction re,im;			//  member objects
 public:
	ComplexFrac(int,int);  // Constructor
	void print() const;
};

#endif
