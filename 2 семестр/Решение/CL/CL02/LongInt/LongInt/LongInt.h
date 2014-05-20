#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

const int BASE = 1000000000;

using namespace std;

int lngInt(int k)
	{
		int c = 0;
		while(k != 0)
		{
			k = k/10;
			c++;
		}

		return c;
	}

	string getNSpace(int n, char count = ' ')
	{
		string s = "";
		for (;(int)s.length() < n-1; s += count);
		return s;
	}

class LongInt
{
	vector<int> _num;
	bool _minus;

	void delZero()
	{
		while (_num.size() > 1 &&_num.back() == 0)
			_num.pop_back();
	}

	LongInt _min(LongInt& p, const LongInt& l)
	{
		int carry = 0;

		LongInt t = p;

		for (size_t i = 0; i < l._num.size() || carry; ++i) 
		{
			t._num[i] -= carry + (i < l._num.size() ? l._num[i] : 0);
			carry = t._num[i] < 0;
			if (carry)  t._num[i] += BASE;
		}

		//while (p._num.size() > 1 && p._num.back() == 0)
		//	p._num.pop_back();
		t.delZero();

		return t;
	}

	LongInt plus(LongInt& p, const LongInt& l)
	{
		int carry = 0;
		LongInt t = p;
		for (size_t i = 0; i < max(t._num.size(), l._num.size()) || carry; ++i) 
		{
			if (i == t._num.size())
				t._num.push_back(0);
			t._num[i] += carry + (i < l._num.size() ? l._num[i] : 0);
			carry = t._num[i] >= BASE;
			if (carry)  t._num[i] -= BASE;
		}

		return t;
	}

	LongInt subadd(LongInt& p, LongInt& l, bool add = true)
	{
		bool m;
		if (!add)
		if (l._minus) 
		{
			LongInt c(l);
			c._minus = false;
			return subadd(p, c);
		}

		LongInt t = p;

		if (add) m = (p._minus == l._minus);
		else m = p._minus && l._minus;

		if (m)
		{
			return plus(t, l);
		} else
		{
			if (t > l)
			{
				t = _min(t, l);
			}
			else 
			{
				t = _min(l, t);
				t._minus = (!add)?true:l._minus;
			}
		}

		return t;
	}

	bool operator>(const LongInt& l)
	{
		if (_num.size() < l._num.size()) return false;
		if (_num.size() > l._num.size()) return true;

		for (int i = 0; i < (int)_num.size(); i++)
		{
			if (_num[i] < l._num[i]) return false;
			if (_num[i] > l._num[i]) return true;
		}

		return false;
	}

	bool operator<(const LongInt& l)
	{
		return !(*this > l);
	}

	void plusInt(int k)
	{
		LongInt c;
		if (k < 0) 
		{
			c._minus = true;
			k = abs(k);
		}
		while (k > 0)
		{
			if (k >= BASE) c._num.push_back(0);
			else c._num.push_back(k);
			k = k / BASE;
		}

		*this = *this + c;
	}

	bool operator==(const LongInt& l)
	{
		if (_num.size() != l._num.size()) return false;

		for (int i = 0; i < (int)_num.size(); i++)
			if (_num[i] != l._num[i]) return false;

		return true;
	}

	bool operator==(int l)
	{
		if (_num.size() > 1) return false;

		return _num[0] == l;
	}

public:
	LongInt(){_minus = false;}
	LongInt(int ch, bool sz = false)
	{
		if (sz)
		{
			for (int i = 0; i < ch; i ++)
				_num.push_back(0);
		} else {
		_num.push_back(0);
		plusInt(ch);
		_minus = ch < 0;}
	}
	~LongInt(){}

	void operator<<(string str)
	{
		if (str[0] == '-')
		{
			str = str.substr(1, str.length()-1);
			_minus = true;
		}
		for (int i = (int)str.length(); i > 0 ; i-=9)
		{
			if (i < 9)
				_num.push_back (atoi (str.substr (0, i).c_str()));
			else
				_num.push_back (atoi (str.substr (i-9, 9).c_str()));
		}
	}

	LongInt operator^(int k)
	{
		if (k == 0)
		{
			LongInt c(1);
			return c;
		}

		LongInt c(1), p(*this);
		for (int i = 0; i < k; i++)
			c = c * p;

		if (_minus && (k%2 != 0)) c._minus = true;

		return c;
	}

	LongInt operator+(LongInt& l)
	{
		return subadd(*this, l);
	}

	LongInt operator-(LongInt& l)
	{
		return subadd(*this, l, false);
	}

	LongInt operator*(int b)
	{
		int carry = 0;
		bool m;

		if ((b < 0) == _minus) m = false;
		if (b < 0 || _minus) m = true;

		b = abs(b);

		LongInt t = *this;

		for (size_t i = 0; i < t._num.size() || carry; ++i) 
		{
			if (i == t._num.size())
				t._num.push_back (0);
			long long cur = carry + t._num[i] * 1ll * b;
			t._num[i] = int (cur % BASE);
			carry = int (cur / BASE);
		}
		while (t._num.size() > 1 && t._num.back() == 0)
			t._num.pop_back();

		t._minus = m;

		return t;
	}

	LongInt operator*(LongInt& l)
	{
		LongInt c (_num.size() + l._num.size(), true);
		bool m;
		LongInt t = *this;

		if (l._minus== _minus) m = false;
		if (l._minus || _minus) m = true;

		for (size_t i = 0; i < t._num.size(); ++i)
			for (int j = 0, carry = 0; j < (int)l._num.size() || carry; ++j) 
			{
				long long cur = c._num[i+j] + t._num[i] * 1ll * (j < (int)l._num.size() ? l._num[j] : 0) + carry;
				c._num[i+j] = int (cur % BASE);
				carry = int (cur / BASE);
			}
		while (c._num.size() > 1 && c._num.back() == 0)
			c._num.pop_back();

		c._minus = m;

		return c;
	}

	LongInt operator/(LongInt& p)
	{
		if(*this < p) 
		{
			*this = LongInt();
			return *this;
		}

		LongInt tmp = *this;
		LongInt tmp2 = p;

		bool m;

		if (p._minus== _minus) m = false;
		if (p._minus || _minus) m = true;

		LongInt res(1);
		while(1)
		{
			if(tmp < p) break;
			int k = tmp._num.size() - tmp2._num.size();
			if(k > 0) k--; 
			tmp = tmp - tmp2;
			res.plusInt(1);//LongInt(BASE)^k;
		}

		res._minus = m;
		
		return res;
	}

	friend ostream& operator<<(ostream &os, LongInt const &c) 
	{ 
		if (c._num.empty()) return os << 0;
		string s = "", vs;

		if (c._minus) s = "-";

		for (int i = c._num.size()-1; i >= 0 ; i--)
		{
			if (c._num[i] == 0 && c._num.size() > 1)
				vs = getNSpace(9 - lngInt(c._num[i]), '0');
			else vs = "";

			vs += to_string(c._num[i]);
			s += vs;
		}
		
		return os << s;
	}

	friend istream& operator>>(istream &input, LongInt &c)
	{ 
		string s;
		input >> s;
		c<<s;
		
		return input;
	}
};
