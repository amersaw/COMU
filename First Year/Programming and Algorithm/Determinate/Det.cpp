#include<iostream>
#include<fstream>

using namespace std;

ifstream fin("Matrix.in");
ofstream fout("Matrix.out");
int main()
{
	int p;
	fin >> p;

	double** a;
	a = new double*[p];
	for (int i = 0; i < p; ++i)
		a[i] = new double[p];

	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < p; j++)
		{
			fin >> a[i][j];
		}
	}


	for (int m = 0; m < p - 1; m++)
	{
	    if(a[m][m]==0)
	    {
	        int c;
    	    for( c =1; c<p-m;c++)
    	    {
    	        if(a[m+1][m]!=0)
    	        {
    	            for(int r=m;r<p;r++)
    	            {
    	                double t=a[m][m];
    	                a[m][m]=a[m+1][m];
    	                a[m+1][m]=t;
    	            }
    	            break;
    	        }
    	    }
    	    if(c==p-m)
    	    {
    	        fout<<0;
    	        return 0;
    	    }
	    }
	    
		for (int i = m; i < p -1; i++)
		{
			double k = -a[i + 1][m] / a[m][m] ;
			for (int j = m; j < p; j++)
			{
				a[i + 1][j] = a[m][j] * k + a[i + 1][j];
			}
		}
	}

	int d = 1;
	for (int i = 0; i < p; i++)
	{
		d *= a[i][i];
	}
    fout<<d;
	for (int i = 0; i < p; ++i)
	{
		delete[] a[i];
		a[i] = NULL;
	}

	return 0;
}