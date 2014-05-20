#pragma once

template <typename T>
class CircleBuffer
{
	T* _array;
	int _maxSize;
	int _counter;
	int _length;
	
	int _end;

	int begin()
	{
		return _counter%_maxSize;
	}

public:
	CircleBuffer(int maxSize)
	{
		_maxSize = maxSize>0?maxSize:1;
		_array = new T[_maxSize];
		_counter = 0;
		_length = 0;
		_end = 0;
	}

	~CircleBuffer()
	{
		delete[] _array;
	}

	void push(T val)
	{
		if (_counter/_maxSize >= 1)
			_end = (_end == (_maxSize-1))?0:_end+1;

		_array[begin()] = val;
		_counter++;
		_length = (_length==_maxSize)?_length:_length+1;
	}

	T pop()
	{
		if (_length == 0)
		{
			fputs( "Buffer is empty\n", stderr);
			abort();
		}

		T v = _array[_end];
		_end = (_end == (_maxSize-1))?0:_end+1;
		_length--;
		return v;
	}

	void trace(bool order = false)
	{
		if (order)
		{
			int i = 0, k = _end, l;
			l = min(_maxSize, _length);

			cout << _length << endl;

			while (i < l)
			{
				cout << _array[k] << " ";
				k = (k == (_maxSize-1))?0:k+1;
				i++;
			}

			return;
		}

		for (int i = 0; i < min(_maxSize, _length); i++)
			cout << _array[i] << " ";
	}


};