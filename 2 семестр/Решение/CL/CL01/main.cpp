#include <iostream>

#include "CompexNumber.h"
#include "Polynom.h"

using namespace std;

int main()
{
	Polynom<ComplexNumber> p1, p2;

	//1
	
	p1.push(ComplexNumber(2, 2));
	p1.push(ComplexNumber(1.4, 7));
	p1.push(ComplexNumber(0, -2));

	p2.push(ComplexNumber(2, 2));
	p2.push(ComplexNumber(1.4, 7));
	p2.push(ComplexNumber(0, -2));

	p1 = p1/p2;
	p1.trace();
	

	p1.trace(); 

	getchar();
	return 0;
}