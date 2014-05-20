#include <iostream>
#include "Array2d.h"

using namespace std;

void gauss(Array2d<double>& a)
{
	int k = 0;
	int n = 2;
	while(k < a.height())
	{
		for (int i = k+1; i < a.height(); i++)
		{
			double coef = a[i][k]/a[k][k];

			for (int j = k; j < a.width(); j ++)
				a[i][j] -= a[k][j]*coef;
		}

		k++; //n++;
	}
}

double det(Array2d<double> a)
{
	if (a.width() != a.height()) abort();
	gauss(a);

	double res = 1;

	for (unsigned int i = 0; i < a.width(); i ++)
		res *= a[i][i];

	return res;
}

int main()
{
	setlocale(0, "russian");

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

	a.trace();
	cout << endl << endl;
	
	//gauss(a);

	a.trace();

	cout << endl << det(a);

	system("pause");
	return 0;
}