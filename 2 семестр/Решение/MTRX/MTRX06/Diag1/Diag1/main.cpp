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

int indexMinLine(Array2d<double> a, int ind)
{   
	int min = a[ind][0];
	int index = 0;
	for (int i = 0; i < a.width(); i++)
	{
		if (min > a[ind][i]) 
		{
			min = a[ind][i];
			index = i;
		}
	}
	return index;
}

int indexMaxColumn(Array2d<double> a, int ind)
{
	int max = a[0][ind];
	int index = 0;

	for (int i = 0; i < a.height(); i++)
	{
		if (max < a[i][ind]) 
		{
			max = a[i][ind];
			index=i;
		}
	}
	return index;
}

void createRandomMatrix(Array2d<double>& a)
{
	srand(time(NULL));
	for (int i = 0; i < a.height(); i++)
		for (int j = 0; j < a.width(); j++)
			a[i][j] = rand()%100;
}

void createMatrixWithSaddlePoint(Array2d<double>& a)
{
	srand(time(NULL));
	int x = rand()%a.width();

	int k = indexMaxColumn(a, x);

	for (int i = 0; i < a.width(); i++)
		if (i != x) if (a[k][i] < a[k][x] ) a[k][i]+=a[k][x];
}

void findSaddlePoin(Array2d<double> a)
{   
	bool check = false;
	
	for (int i = 0; i < a.height(); i++)
	{
		int ind = indexMinLine(a, i);

		if (i == indexMaxColumn(a, ind)) 
		{
			cout << '(' << a[i][ind] << "  " << ind+1 << ';' << i+1 << ')';
			check = true;
		}
	}
	cout << endl;
	if (!check) cout << "Saddle point didn't found" << endl;
}

int main()
{
	setlocale(0, "russian");

	unsigned int w, h;
	cout << "¬ведите размер массива:" << endl;
	cin >> w >> h;

	Array2d<double> a(w, h);
	
	/*
	cout << "¬ведите элементы:" << endl;
	for (unsigned int i = 0; i < h; i++)
		for (unsigned int j = 0; j < w; j++)
		{
			cin >> c;
			a[i][j] = c;
		}
	*/

	createRandomMatrix(a);

	a.trace(); 


	createMatrixWithSaddlePoint(a);

	a.trace();

	cout << endl;
	findSaddlePoin(a);

	system("pause");
	return 0;
}