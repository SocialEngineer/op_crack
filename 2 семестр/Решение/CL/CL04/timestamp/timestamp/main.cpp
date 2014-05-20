#include <iostream>
#include "TimeStamp.h"

using namespace std;

int main()
{
	//(הה.לל.דדדד h:m:s)
	TimeStamp t1("12.02.2014 00:00:00"), t2("12.02.2014 23:47:04");

	cout << t2 - t1 << endl;

	system("pause");
	return 0;
}