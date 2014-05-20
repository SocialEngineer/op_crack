#include <iostream>
#include "Array2d.h"

using namespace std;

int main()
{
	int w = 5, h = 2;
	Array2d<int> a(w,  h);

	for (int i = 0; i < w; i++)
		for(int j = 0; j < h; j++)
			a[j][i] = rand()%100; 

	a[0][1] = 200;

	a.trace();

	return 0;
}