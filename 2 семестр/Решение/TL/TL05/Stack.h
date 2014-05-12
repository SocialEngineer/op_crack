#pragma once

template <typename T>
class Stack
{
	T* _array;
	int _maxSize;
	int _length;
public:
	Stack(int maxSize)
	{
		_maxSize = maxSize;
		_array = new T[_maxSize];
		_length = 0;
	}

	~Stack()
	{
		delete[] _array;
	}

	void push(T val)
	{
		if (_length == _maxSize)
		{
			fputs( "Stack overflow\n", stderr);
			abort();
		}
		_array[_length] = val;
		_length++;
	}

	T pop()
	{
		if (_length == 0)
		{
			fputs( "Stack underflow\n", stderr);
			abort();
		}
		_length--;
		return _array[_length];
	}

	int length()
	{
		return _length;
	}
};