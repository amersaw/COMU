// e412.cpp
// main program
#include <cstdlib>
#include <iostream>

#include"complex.h"

//----- Main Function -----
int main()
{
	ComplexFrac cf(2,5);				// A complex number is created
	cf.print();							// Complex number is printed on the screen

    system("PAUSE");
    return EXIT_SUCCESS;
}
