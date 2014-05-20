#include <iostream>
#include "Array2d.h"
#include <ctime>

/*
1 2 4 2 4
3 4 32 4 5
0 3 3 3 2 
9 8 -3 2 3
8 4 2 4 5
*/

using namespace std;

int gauss(Array2d<double>& a)
{
	int k = 0;
	int n = 2;
	int sw = 0;
	while(k < a.height())
	{
		for (int i = k+1; i < a.height(); i++)
		{
			if (a[i][k] == 0) continue;

			if (a[k][k] == 0) 
			{
				sw++;
				a.swap(k, i);
			}
			double coef = a[i][k]/a[k][k];

			for (int j = k; j < a.width(); j ++)
				a[i][j] -= a[k][j]*coef;
		}

		k++; //n++;
	}

	return sw;
}

double det(Array2d<double> a)
{
	if (a.width() != a.height()) abort();
	int sw = gauss(a);

	double res = 1;

	for (unsigned int i = 0; i < a.width(); i ++)
		res *= a[i][i];

	return res*(sw%2==0?1:-1);
}

double det2(Array2d<double> a, bool minus = false)
{
	if (a.width() == 2) return a[0][0]*a[1][1]-a[0][1]*a[1][0];

	double res = 0;
	for (int i = 0; i < a.width(); i++)
	{
		double c = a[0][i]*det2(a.minor(i, 0), !minus)*(i%2?-1:+1);

		res += c;
	}
	
	return res;
}

int main()
{
	setlocale(0, "russian");
	int  t0, d1, d2;

	unsigned int w, h;
	cout << "¬ведите размер массива:" << endl;
	cin >> w >> h;

	double c;
	Array2d<double> a(w, h);
	
	cout << "¬ведите элементы:" << endl;
	for (unsigned int i = 0; i < h; i++)
		for (unsigned int j = 0; j < w; j++)
		{
			cin >> c;
			a[i][j] = c;
		}

	cout << endl << endl;

	t0 = clock();
		cout << endl << det2(a) << endl;
	d1 = clock() - t0;

	t0 = clock();
		cout << endl << det(a) << endl;
	d2 = clock() - t0;

	cout << endl << d1 << "  :  " << d2 << endl;

	system("pause");
	return 0;
}