#include <iostream>
#include"fraction.h"
using namespace std;

int main()
{
    Fraction f1(1,2),f2(3,4),f3;
    f3=f1+f2;
    f3.print();
    cout << "Hello world!" << endl;
    return 0;
}
