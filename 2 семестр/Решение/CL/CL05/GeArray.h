#ifndef _GEARRAY_H
#define _GEARRAY_H

template<typename T> class GeArray{
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
};

template<typename T> GeArray<T>::GeArray()
{
    	_arr = 0;
	_size = 0;
};

template<typename T> GeArray<T>::GeArray(int size)
{
    	_size = size;
    	_arr = new T [_size];
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
	T* new_arr = new T[_size + 1];
	for (int i = 0; i < _size; i++)
		new_arr[i] = _arr[i];
	new_arr[_size] = el;
	delete _arr;
	_arr = new_arr;
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
