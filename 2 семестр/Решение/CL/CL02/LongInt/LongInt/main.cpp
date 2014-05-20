#include <iostream>

#include "LongInt.h"

using namespace std;

int main()
{
	LongInt a, b;
	int k;
	
	setlocale(LC_ALL, "Russian");

	cout << "¬ведите первое число: " << endl;
	cin >> a;
	cout << "\n¬ведите второе число: " << endl;
	cin >> b;
	cout << "\n¬ведите значение дл€ возведени€ в степень 1го числа: " << endl;
	cin >> k;

	LongInt t1 = a + b;
	LongInt t2 = a - b;
	LongInt t3 = a * b;
	LongInt t4 = a / b;
	LongInt t5 = a ^ k;
	
	cout << "A + B = " << t1 << endl << "A - B = " << t2 << endl << "A * B = " << t3 << endl << "A / B = " << t4 << endl << "A ^ k = " << t5 << endl;

	//cout << z1;
	//cout << (z2-z1);

	system("pause");
	return 0;
}