#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iostream>

#define uint unsigned int

template <typename T>
class Array2d
{
    public:
        Array2d(uint width, uint height)
		{
			_width = width;
			_height = height;
			_data = new T*[_height];

			for (int i = 0; i < _height; i++)
				_data[i] = new T[_width];
		}

		~Array2d(){}

        T* operator[](uint x) const
		{
			return _data[x];
		}

		bool operator==(Array2d arr)
		{
			if (width() == arr.width() &&
						height() == arr.height())
			{
				for (int i = 0; i < _width; i++)
					for (int j = 0; j < _height; j++)
						if (_data[j][i] != arr[j][i]) return false;
			} else return false;

			return true;
		}

		bool operator!=(Array2d arr)
		{
			if (*this == arr) return false;

			return true;
		}

		uint width()
		{
			return _width;
		}

		uint height()
		{
			return _height;
		}

        void trace(void)
		{
			for (int i = 0; i < _height; i++)
			{
				for (int j = 0; j < _width; j++)
				{
					std::cout << _data[i][j] << "  ";
				}
				std::cout << "\n";
			}
		}
    private:
        uint _width, _height;
        T** _data;
};


#endif // ARRAY2D_H
