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

void createRandomMatrix(Array2d<double>& a)
{
	srand(time(NULL));
	for (int i = 0; i < a.height(); i++)
		for (int j = 0; j < a.width(); j++)
			a[i][j] = rand()%100;
}

bool check(int i, int j, int k)
{
	if (i != j) return true;

	if (i <= k) return false;
	return true;
}

void findMaxWithOut(Array2d<double>& a, int k = -1)
{
	if (k == 9) return;
	double max = 0;
	int mx = 0, my = 0;

	for (int i = 0; i < a.height(); i++)
		for (int j = 0; j < a.width(); j++)
		{
			if (check(i, j, k))
			{
				if (a[i][j] > max)
				{
					max = a[i][j];
					mx = j; my = i;
				}
			}
		}

		a[my][mx] = a[k+1][k+1];
		a[k+1][k+1] = max;
		findMaxWithOut(a, k+1);
}

int main()
{
	setlocale(0, "russian");

	Array2d<double> a(10, 10);
	
	createRandomMatrix(a);
	
	a.trace(4);

	cout << endl << endl;

	findMaxWithOut(a);
	a.trace(4);

	system("pause");
	return 0;
}