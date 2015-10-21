// fraction.h
// Decleration of fractions
#ifndef _fraction_           // to include only once
#define _fraction_

class Fraction{       // A class to define fractions
   int numerator,denominator;
 public:
    Fraction operator+(const Fraction) const;
    Fraction(int, int);
    Fraction();
	void print() const;
};

#endif
