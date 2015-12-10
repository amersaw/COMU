#include <iostream>
using namespace std;

float fraction(int num, int denom)
{
	if(denom==0) throw "Divided by zero";
	if(denom<0) throw "Negative Denominator";
	if(denom>1000) throw -1;
	return static_cast<float>(num)/denom;
}

int main()
{
	int numerator,denumerator;
	cout << endl << "Enter the numerator ";
	cin >> numerator;
	cout << endl << "Enter the denumerator ";
	cin >> denumerator;
	try{
		cout << fraction(numerator,denumerator);
	}
	catch (const char * result){		// catch for char*s
		cout << endl << result;
	}
	catch (int t ){							// catch for ints
		cout << endl << "Hata Kodu : " << t << endl;
	}
	
	
	
	cout << endl << "End of Program";
	
	system("pause");
	return 0;
}
