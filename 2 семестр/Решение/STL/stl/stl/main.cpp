#include <iostream>
#include "DcList.h"
#include "DcMap.h"

using namespace std;

#define STL2

int main()
{
	setlocale(LC_ALL, "Russian");
	DcList d;
	d.load();

#ifdef STL2
	d.stl2('q');
#endif
#ifdef STL3
	d.stl3('ч');
#endif
#ifdef STL4
	d.stl4("incertitude", 4, 0, true);
#endif
#ifdef STL5
	d.stl5();
#endif
#ifdef STL6
	d.stl6("ояние неопределен");
#endif
#ifdef STL7
	d.stl7();
#endif
#ifdef STL8
	d.stl8(5);
#endif
#ifdef STL9
	d.stl9("состояние неопределенности");
#endif
#ifdef STL10
	d.stl10(true);
#endif
#ifdef STL11
	d.stl10("состояние неопределенности", true);
#endif
#ifdef STL12
	d.stl10("состояние неопределенности", true);
#endif


	system("pause");
	return 0;
}