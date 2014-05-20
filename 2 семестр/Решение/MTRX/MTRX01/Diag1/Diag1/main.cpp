#include <iostream>
#include "Array2d.h"

using namespace std;

int main()
{
	setlocale(0, "russian");

	unsigned int w, h;
	cout << "¬ведите размер массива:" << endl;
	cin >> w >> h;

	Array2d<int> a(w, h);

	for (int i = 0; i < w; i ++)
		for (int j = 0; j < h; j ++)
			a[i][j] = (i+j)%2?1:0;

	a.trace();

	system("pause");
	return 0;
}