#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iostream>
/*
1 2 4 2 4
3 4 32 4 5
0 3 3 3 2 
9 8 -3 2 3
8 4 2 4 5
*/

#define uint unsigned int

template <typename T>
class Array2d
{
    public:
        Array2d(uint width, uint height)
		{
			_width = width;
			_height = height;
			_data = new T*[_width];

			for (int i = 0; i < _width; i++)
				_data[i] = new T[_height];
		}

        ~Array2d()
		{
			//for (int i = 0; i < _width; i++)
			///	delete[] _data[i];
			//delete[] _data;
		}

        T* operator[](uint x) const
		{
			return _data[x];
		}

		Array2d<T> minor(int x, int y)
		{
			Array2d<T> c(_width-1, _height-1);

			int xx = 0, yy = 0;

			for (int i = 0; i < _width; i++)
			{
				for (int j = 0; j < _height; j++)
				{
					if (i != x && j != y)
					{
						c[yy][xx] = _data[j][i];
						yy++;
						if (yy == c.width()) 
						{
							yy = 0;
							xx++;
						}
					}
				}
			}

			return c;
		}

		bool operator==(Array2d arr)
		{
			if (width() == arr.width() &&
						height() == arr.height())
			{
				for (int i = 0; i < _width; i++)
					for (int j = 0; j < _height; j++)
						if (_data[i][j] != arr[i][j]) return false;
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

		// меняем строки
		void swap(int ki, int kj)
		{
			T p;
			for (size_t i = 0; i < _width; i++)
			{
				p = _data[ki][i];
				_data[ki][i] = _data[kj][i];
				_data[kj][i] = p;
			}
		}

        void trace(void)
		{
			for (int i = 0; i < _width; i++)
			{
				for (int j = 0; j < _height; j++)
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
