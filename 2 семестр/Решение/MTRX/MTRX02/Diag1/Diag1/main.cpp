#include <iostream>
#include "Array2d.h"

using namespace std;

int main()
{
	setlocale(0, "russian");

	unsigned int w, h;
	cout << "¬ведите размер массива:" << endl;
	cin >> w >> h;

	int wl = 0, wr = h, ht = 0, hb = w, mx = w*h, k = 1;
	bool rw = false, rh = false;
	int row = 0, column = 0;

	Array2d<int> a(w, h);

	while (k <= mx)
	{
		if (!rw)
		{
			for (int i = wl; i < wr; i++)
			{
				a[rh?hb-1:ht][i] = k;
				k++;
			}
			ht++;
		} else
		{
			for (int i = wr-1; i >= wl; i--)
			{
				a[rh?hb-1:ht][i] = k;
				k++;
			}
			hb--;
		}
		rw = !rw;

		if (!rh)
		{
			for (int i = ht; i < hb; i++)
			{
				a[i][rw?wr-1:wl] = k;
				k++;
			}
			wr--;
		} else
		{
			for (int i = hb-1; i >= ht; i--)
			{
				a[i][rw?wr-1:wl] = k;
				k++;
			}
			wl++;
		}
		rh = !rh;
	}
	
	a.trace();

	system("pause");
	return 0;
}