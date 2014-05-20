#include <iostream>
#include "MDate.h"

using namespace std;

int main()
{
	MDate d1("20.06.2014"), d2("20.03.2014");

	cout << d1 << ", " << d2 << " : " << (d1-d2) << endl;
	d1++;
	cout << d1 << endl;

	system("pause");
	return 0;
}