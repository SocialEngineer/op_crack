#include <iostream>
#include "Array2d.h"
#include <fstream>
#include <string>
#include <vector>
/*
1 2 4 2 4
3 4 32 4 5
0 3 3 3 2 
9 8 -3 2 3
8 4 2 4 5
*/

using namespace std;

int finfMax(vector<double>&v)
{
	double mx = -2.22507e-308;
	int k = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] > mx)
		{
			mx = v[i];
			k = i;
		}
	}

	v[k] = -2.22507e-308;

	return k;
}


int main()
{
	setlocale(0, "russian");

	int w, h, x = 0, y = 0;
	double c;

	ifstream f("mtrx.txt");
	f >> w >> h;
	Array2d<double> a(w, h);
	vector<double> sum;

	for (int i = 0; i < h; i++)
	{
		sum.push_back(0);
	}

	while(!f.eof())
	{
		f >> c;

		a[y][x] = c;
		x ++;
		sum[y] += c;
		if (x == w)
		{
			x = 0;
			y++;
		}
	}


	f.close();

	a.trace();

	ofstream of("output.txt");

	for (int i = 0; i < sum.size(); i++)
	{
		int t = finfMax(sum);

		for (int j = 0; j < w; j++)
			of << a[t][j] << "  ";
		of << endl;
	}
	of.close();

	system("pause");
	return 0;
}