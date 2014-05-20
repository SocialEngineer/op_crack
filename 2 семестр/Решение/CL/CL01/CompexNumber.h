#pragma once

#include <iostream>
#include <ostream>


using namespace std;

class ComplexNumber
{
	
public:
	double a;
	double b;
	ComplexNumber() { a = 0; b = 0;}
	ComplexNumber(double a, double b){ this->a = a; this->b = b;}
	~ComplexNumber(){};

	ComplexNumber& operator+(ComplexNumber& c)
	{
		a += c.a;
		b += c.b;
		return *this;
	}

	ComplexNumber& operator-(ComplexNumber& c)
	{
		a -= c.a;
		b -= c.b;
		return *this;
	}

	ComplexNumber& operator-(double& c)
	{
		a -= c;
		return *this;
	}

	ComplexNumber& operator-=(double& c)
	{
		a -= c;
		return *this;
	}

	ComplexNumber& operator-=(ComplexNumber& c)
	{
		*this = *this - c;
		return *this;
	}

	ComplexNumber& operator+=(double& c)
	{
		a += c;
		return *this;
	}

	ComplexNumber& operator+=(ComplexNumber& c)
	{
		*this = *this + c;
		return *this;
	}

	ComplexNumber& operator*(ComplexNumber& c)
	{
		double aa = a;

		a = a*c.a - b*c.b;
		b = aa*c.b + b*c.a;
		return *this;
	}

	ComplexNumber& operator/(ComplexNumber& c)
	{
		double sq = c.a*c.a + c.b*c.b;
		double aa = a;

		a = (a*c.a + b*c.b)/sq;
		b = (aa*c.b - b*c.a)/sq;
		return *this;
	}

	ComplexNumber& operator*(const double& c)
	{
		a = a*c;
		b = b*c;
		return *this;
	}

	ComplexNumber& operator/(const double& c)
	{
		a = a/c;
		b = b/c;
		return *this;
	}

	ComplexNumber& operator=(const ComplexNumber& c)
	{
		a = c.a;
		b = c.b;
		return *this;
	}

	ComplexNumber& operator=(const double& c)
	{
		a = c;
		b = 0;
		return *this;
	}
	
	bool operator==(const ComplexNumber& c) const 
	{
		return (a == c.a && b == c.b);
	}

	bool operator==(const double& c) const 
	{
		if (b != 0) return false;
		return a == c;
	}

	bool operator!=(const ComplexNumber& c) const 
	{
		return !(*this == c);
	}

	bool operator!=(const double& c) const 
	{
		if (b != 0) return true;
		return !(a == c);
	}

	friend ostream& operator<<(ostream &os, ComplexNumber const &c) 
	{ 
		bool fl = c.b < 0;
		if (fl) return os << c.a << c.b << "i"; 
		else return os << c.a << "+" << c.b << "i";
	}
};