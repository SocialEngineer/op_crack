#ifndef _GEARRAY_H
#define _GEARRAY_H

template<typename T> class GeArray
{
	T* _arr;
	public:
	unsigned int _size;
	GeArray();
    	GeArray(int);
    	GeArray(const GeArray &);
	~GeArray();
	T& operator[](unsigned int index); //обращение к элементу по индексу
	void add(const T&); // добавление элемента в конец массива
	void del_el(unsigned int place); //удаление элемента по индексу
	void Print();//вывод массива на экран
	int _realsize;

	class Ptr{
		T *_current;
	public:
		friend class GeArray;
		Ptr& operator--(){if (_current) _current--;return *this;} //go to the previous element
		Ptr& operator++ (){if (_current) _current++;return *this;}; // Перемещает к следующему элементу
		T& getData(){
			if (_current)
				return *_current;
			throw std::out_of_range("Illegal ptr");
		};// Получение данных, соответствующих _current

		bool canMoveForward(){return (_current-_arr)>0}; //Checking if can move to the next element
		bool canMoveBack(){return _current > _arr}; //Checking if can move to the previous element

		Ptr(){_current = 0;};
		Ptr(const Ptr&p){_current = p._current;};
		bool operator !=(Ptr it)
		{
			if(_current == it._current)
				return 0;
			return 1;
		};
		bool operator ==(Ptr it)
		{
			return (_current == it._current);
		};
	};

	Ptr End()
	{
		Ptr p;
		p._current= _arr + _size;
		return p;
	};

	Ptr getFirstPtr(){
		Ptr p;
		p._current = _arr;
		return p;
	};
};

template<typename T> GeArray<T>::GeArray()
{
    	_arr = 0;
	_size = 0;
	_realsize = 0;
};

template<typename T> GeArray<T>::GeArray(int size)
{
	_size = 0;
	_realsize = size;
    	_arr = new T [_realsize];
}

template<typename T> GeArray<T>::GeArray(const GeArray<T> &arr){
    	_size = arr._size;
    	_arr = new T [_size];
 
    	for (int i = 0; i < _size; i++)
        	_arr[i] = arr._arr[i];
}

template<typename T> GeArray<T>::~GeArray()
{
	delete [] _arr;
};

template<typename T> T& GeArray<T>::operator[](unsigned int index)
{
	return _arr[index];
};

template<typename T> void GeArray<T>::add(const T& el)
{
	if (_realsize <= _size){
		_realsize *= 2;
		T* new_arr = new T[_realsize];
		for (int i = 0; i < _size; i++)
			new_arr[i] = _arr[i];
		new_arr[_size] = el;
		delete[] _arr;
		_arr = new_arr; 
	} else
	{
		_arr[_size] = el;
	}
	//_arr = (T*)realloc(_arr, _size+1);
	_size++;
};

template<typename T> void GeArray<T>::Print()
{
	for (int i = 0; i < _size; i++)
		cout << _arr[i] << " ";
	cout << endl;
};

template<typename T> void GeArray<T>::del_el(unsigned int place)
{
	T* new_arr = new T[_size - 1];
	for (int i = 0; i < place; i++)
		new_arr[i] = _arr[i];
	for (int i = place; i < _size; i++)
		new_arr[i] = _arr[i + 1];
	delete _arr;
	_arr=new_arr;
	_size--;
};
#endif // _GEARRAY_H
