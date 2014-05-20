#pragma once

#include <iostream>
#include <string>
#include "MDate.h"

using namespace std;


class TimeStamp
{
	MDate _date;
	int _h;
	int _m;
	int _s;

	void parse(string str)
	{
		int k = findInStr(str, ' ');
		if (k == -1) abort();
		string data = str.substr(0, k);
		str = str.substr(k+1, str.length()-k);
		_date.set(data);

		k = findInStr(str, ':');
		if (k == -1) abort();

		_h = atoi(str.substr(0, k).c_str());
		str = str.substr(k+1, str.length()-k);
		if (_h >= 24) abort();

		k = findInStr(str, ':');
		if (k == -1) abort();

		_m = atoi(str.substr(0, k).c_str());
		if (_m > 60) abort();
		str = str.substr(k+1, str.length()-k);

		_s = atoi(str.c_str());
		if (_s > 60) abort();

		if (_s < 0 || _m < 0 || _h < 0) abort();
	}
public:
	TimeStamp(string str)
	{
		parse(str);
	}

	~TimeStamp(){}

	void set(string str)
	{
		parse(str);
	}

	
	friend ostream& operator<<(ostream &os, TimeStamp &t) 
	{ 
		os << t._date << " " << to_string(t._h) << ":" << to_string(t._m) << ":" << to_string(t._s);
		return os;
	}
	
	friend istream& operator>>(istream &input, TimeStamp &t)
	{ 
		string s;
		input >> s;
		
		t.set(s);
		
		return input;
	}

	int getSec()
	{
		return _h*3600 + _m*60 + _s;
	}

	long operator-(TimeStamp& t)
	{
		long a = (_date - t._date) * 24 * 3600;
		return a + (getSec() - t.getSec());
	}
};