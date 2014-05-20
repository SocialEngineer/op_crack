#pragma once

#include <iostream>
#include <string>

using namespace std;

int findInStr(string s, char c, int count = 1)
{
	for (size_t i = 0; i < s.length(); i++)
		if (s[i] == c)
		{
			count--;
			if (count == 0)
				return i;
		}
	return -1;
}

int dayInMonth(int m, int year)
{
	int days = 31 - ((m - 1) % 7) %2;
	if (m == 2)
	{
		if(year % 4 || (year % 100 == 0 && year % 400))
			days = 28;
		else days = 29;
	}

	return days;
}

class MDate
{
	int _d;
	int _m;
	int _y;

	long getDaysCount()
	{
		long res = 0;
		for (int i = 1; i < _y; i++)
		{
			if(_y % 4 || (_y % 100 == 0 && _y % 400))
				res += 365;
			else res += 366;
		}

		for (int i = 1; i <= _m; i++)
			res += dayInMonth(i+1, _y);
		res += _d;

		return res;
	}

	void parse(string str)
	{
		int k = findInStr(str, '.');
		if (k == -1) abort();

		_d = atoi(str.substr(0, k).c_str());
		str = str.substr(k+1, str.length()-k);

		k = findInStr(str, '.');
		if (k == -1) abort();

		_m = atoi(str.substr(0, k).c_str());
		if (_m > 12) abort();
		str = str.substr(k+1, str.length()-k);

		if (str.length() < 4) abort();
		_y = atoi(str.c_str());

		if (_y < 0 || _m <= 0 || _d <= 0) abort();
		if (_d > dayInMonth(_m, _y)) abort();
	}

public:
	MDate(string str)
	{
		parse(str);
	}
	~MDate(){}

	void set(string str)
	{
		parse(str);
	}

	int diffInDays(MDate& md)
	{
		return getDaysCount() - md.getDaysCount();
	}

	friend ostream& operator<<(ostream &os, MDate &md) 
	{ 
		os << to_string(md._d) << '.' << to_string(md._m) << '.' << to_string(md._y);
		return os;
	}

	friend istream& operator>>(istream &input, MDate &md)
	{ 
		string s;
		input >> s;
		
		md.set(s);
		
		return input;
	}

	void operator--()
	{
		if (_d > 0) _d--;
		else
		{
			if (_m > 1)
			{
				_m--;
				_d = dayInMonth(_m, _y);
			} else
			{
				_y--;
				_m = 12;
				_d = dayInMonth(_m, _y);
				if (_y < 0) abort();
			}
		}
	}

	void operator++()
	{
		if (_d < dayInMonth(_m, _y)) _d++;
		else
		{
			if (_m < 12)
			{
				_m++;
				_d = 1;
			} else
			{
				_y++;
				_m = 1;
				_d = 1;
			}
		}
	}

	int operator-(MDate& md)
	{
		return diffInDays(md);
	}

};