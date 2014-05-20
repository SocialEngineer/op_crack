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

bool findHorizontX(Array2d<char> a, int k)
{
	int n = 0;
	for (int j = 0; j < a.height(); j++)
	{
		for (int i = 0; i < a.width(); i++)
		{
			if (a[j][i] == 'x') n++;
			if ( n == k) return true;
		}
		n = 0;
	}

	return false;
}

bool findVerticaltX(Array2d<char> a, int k)
{
	int n = 0;
	for (int j = 0; j < a.width(); j++)
	{
		for (int i = 0; i < a.height(); i++)
		{
			if (a[i][j] == 'x') n++;
			if ( n == k) return true;
		}
		n = 0;
	}

	return false;
}

bool dl(Array2d<char> a, int x, int y,  int k)
{
	int n = 0;
	while (true)
	{
		if (a[y][x] == 'x') n++;
		if (n == k) return true;


		y++; x++;
		if (x >= a.width()) return false;
		if (y >= a.height()) return false;
	}
	return false;
}

bool dr(Array2d<char> a, int x, int y,  int k)
{
	int n = 0;
	while (true)
	{
		if (a[y][x] == 'x') n++;
		if (n == k) return true;


		y++; x--;
		if (x < 0) return false;
		if (y >= a.height()) return false;
	}
	return false;
}

bool findDiag(Array2d<char> a, int k)
{
	int n = 0;
	for (int j = 0; j < a.width(); j++)
	{
		for (int i = 0; i < a.height(); i++)
		{
			if (dl(a, j, i, k) || dr(a, j, i, k)) return true;
		}
		n = 0;
	}

	return false;
}

int main()
{
	setlocale(0, "russian");

	unsigned int w, h, k;
	cout << "¬ведите размер массива:" << endl;
	cin >> w >> h;

	cout << "¬ведите число к:" << endl;
	cin >> k;

	Array2d<char> a(w, h);
	
	char c;
	cout << "¬ведите элементы:" << endl;
	for (unsigned int i = 0; i < h; i++)
		for (unsigned int j = 0; j < w; j++)
		{
			cin >> c;
			a[i][j] = c;
		}


	//a.trace();

	bool f = findHorizontX(a, k) || findVerticaltX(a, k) || findDiag(a, k);

	if (f) cout << "YES" << endl;
	else cout << "NO" << endl;

	system("pause");
	return 0;
}