#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include "List3.h"

/*
	d.push(7);
	d.push(2);
	d.push(0);
	d.push(0);
	d.push(3);
	d.push(1);

	d2.push(0);
	d2.push(1);
	d2.push(1);

	d = d / d2;
	*/

using namespace std;

template<typename T>
class Polynom
{
	int _size;
	int _realSize;
	List3<T> _coef;

	T _nothing;

	void updateRealSize()
	{
		for (int i = _size-1; i >= 0; i--)
			if (_coef[i] != 0){
				_realSize = i + 1;
				return;
			}
	}

	Polynom<T>* divmod(Polynom<T>& p, bool div = true)
	{
		Polynom<T> *remainder, *quotient;
		remainder = clone();
		quotient = new Polynom<T>(_realSize - p.realSize() + 1);
	
		for (int i = 0; i < quotient->size(); i++)
		{
			T coeff = (*remainder)[remainder->realSize() - i - 1] / p[p.realSize()-1];
			(*quotient)[quotient->size() - i - 1] = coeff;
			for (int j = 0; j < p.realSize(); j++)
			{
				(*remainder)[remainder->realSize() - i - j - 1] -= coeff * p[p.realSize() - j - 1];
			}
		}

		if (div) return quotient;
		if (!(_realSize - p.realSize()))
			{
				delete remainder;
				remainder = new Polynom<T>(1);
				(*remainder)[0] = 0;
			}
		return remainder;
	}

protected:
	List3<T>* getData()
	{
		return &_coef;
	}

public:
	Polynom()
	{
		_size = 0;
		_realSize = 0;
		_nothing = 0;
	}

	Polynom(int size)
	{
		_size = size;
		for (int i = 0; i < size; i++)
			_coef.push(_nothing);
		_realSize = 0;
	}

	~Polynom(){}

	void push(T val)
	{
		_size++;
		_coef.push(val);
		updateRealSize();
	}

	T& operator[](int i)
	{
		return _coef[i];
	}

	Polynom<T>& operator=(Polynom<T> val)
	{
		_coef = val._coef;
		_size = val.size();
		return *this;
	}

	Polynom<T>& operator+(Polynom<T> p)
	{
		int mx = max(_size, p.size());
		Polynom<T> *pp = new Polynom<T>(mx);

		for (int i = 0; i < min(mx, _size) ; i++)
			(*pp)[i] += _coef[i];

		for (int i = 0; i < min(mx, p.size()); i++)
			(*pp)[i] += p[i];

		(*pp).updateRealSize();
			
		return (*pp);
	}

	Polynom<T>& operator-(Polynom<T> p)
	{
		int mx = max(_size, p.size());
		Polynom<T> *pp = new Polynom<T>(mx);

		for (int i = 0; i < min(mx, _size) ; i++)
			(*pp)[i] -= _coef[i];

		for (int i = 0; i < min(mx, p.size()); i++)
			(*pp)[i] -= p[i];

		(*pp).updateRealSize();
			
		return (*pp);
	}

	Polynom<T>& operator*(Polynom<T> p)
	{
		int mx = _size+p.size();
		Polynom<T> *pp = new Polynom<T>(mx, 0);

		for (int i = 0; i < _size ; i++)
		for (int j = 0; j < p.size(); j++)
			(*pp)[i+j] += p[j] * _coef[i];

		(*pp).updateRealSize();
			
		return (*pp);
	}

	Polynom<T>& operator*(T p)
	{
		Polynom<T> *pp = new Polynom<T>(_size);

		for (int i = 0; i < _size ; i++)
			(*pp)[i] = _coef[i] * p;

		(*pp).updateRealSize();
			
		return (*pp);
	}

	Polynom<T>& operator/(Polynom<T>& p)
	{
		return *divmod(p, true);
	}

	Polynom<T>& operator%(Polynom<T>& p)
	{
		return *divmod(p, false);
	}

	Polynom<T>* clone()
	{
		Polynom<T> *p = new Polynom<T>(_size);
		(*p) = (*p) + (*this);
		(*p)._realSize = _realSize;
		return p;
	}

	int size()
	{
		return _size;
	}

	int realSize()
	{
		return _realSize;
	}

	double solved(double x)
	{
		double res = 0;
		for (int i = _size-1; i >= 0; i--) 
			res += _coef[i]*pow(x, i);
			
		return res;
	}

	void trace()
	{
		for (int i = _size-1; i >= 0; i--)
			if( _coef[i] != 0 )
			cout << "x^" << i << " : " << _coef[i] << endl;

		cout << endl;
	}

};