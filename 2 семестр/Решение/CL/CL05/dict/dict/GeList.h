#pragma once
#include <iostream>
#include <stdexcept>

template<typename T> class GeList
{
	struct node{
		node()  {next=0;previous=0;};
		T data;
		node *next;
		node *previous;

	};

	node *_first;
	node *_last;
	unsigned _size;

public:
	class Ptr{
		node *_current;
	public:
		friend class GeList;
		Ptr& operator--(){if (_current) _current=_current->previous;return *this;} //go to the previous element
		Ptr& operator++ (){if (_current) _current = _current->next;return *this;}; // Перемещает к следующему элементу
		T& getData(){
			if (_current)
				return _current->data;
			throw std::out_of_range("Illegal ptr");
		};// Получение данных, соответствующих _current

		bool canMoveForward(){return _current && _current->next;}; //Checking if can move to the next element
		bool canMoveBack(){return _current && _current->previous;}; //Checking if can move to the previous element

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

	GeList(void){
		_first = 0;
		_size=0;
		_last=0;
	};
	GeList(const GeList&);
	const GeList & operator= (const GeList&);
	~GeList(void);
	T* add(T);
	//T* add(T*);
	GeList<T> add_and_ret(T);
	void clear();
	unsigned int  size()const {return _size;};

	void Sort(Ptr l,Ptr r);
	// Возвращает экземпляр Ptr,
	//соответствующий первому элементу последовательности
	Ptr getFirstPtr(){
		Ptr p;
		p._current = _first;
		return p;
	};
	//соответствующий последнему элементу последовательности
	Ptr getLastPtr(){
		Ptr p;
		p._current = _last;
		return p;
	};
	//соответствующий элементу последовательности, идущему перед первым
	Ptr Begin()
	{
		Ptr p;
		if(_size==0)
			p._current=_first;
		else
		p._current=_first->previous;
		return p;
	};
	//соответствующий элементу последовательности, идущему после последнего
	Ptr End()
	{
		Ptr p;
		if(_size==0)
 			p._current= _first;
 		else
		p._current=_last->next;
		return p;
	};

	bool isEmpty(){
		if (_first==0)
			return true;
		return false;
	};

	void deleteOneElem(Ptr);
	void deleteOneElem(unsigned int N);

	T& back(){
		if (_last) return _last->data;
		throw std::runtime_error("Empty list");
	};
};

template<typename T> void GeList<T>::deleteOneElem(Ptr current)
{
	if (_size == 0)
	{
		return;
	}
	_size--;
		node *tmp=current._current;
 	if(_size==0)
 	{
 		_first=0;
 		_last=0;
 		delete tmp;
 		return;
 	}
	if (tmp == _first)
	{
		tmp->next->previous=0;
		_first=_first->next;
		delete tmp;
		return;
	}
	if (tmp == _last)
	{
		tmp->previous->next=0;
		_last=tmp->previous;
		delete tmp;
		return;
	}
	tmp->next->previous=tmp->previous;
	tmp->previous->next=tmp->next;
	delete tmp;
}
template<typename T> void GeList<T>::deleteOneElem(const unsigned int N)
{
	if (isEmpty() || N>=_size || N<0)
	{
		return;
	}
	Ptr tmp = getFirstPtr();
	for (int i=0; i<N; i++)
	{
		tmp=tmp->next();
	}
	this->deleteOneElem(tmp);
}
template<typename T> GeList<T>::GeList(const GeList &l)
{
   node *p = l._first;
   _first=_last=0;
   _size=0;
   _first=p;
   while (p){
      this->add(p->data);
      p = p->next;
   }
}
template<typename T> GeList<T>::~GeList(void)
{
	clear();
}
template<typename T> const GeList<T>& GeList<T>::operator=(const GeList &l)
{
	if (l._first == this->_first) return *this;
   clear();
   node *p = l._first;
   while (p){
      this->add(p->data);
      p = p->next;
   }
   return *this;
}

template<typename T> void GeList<T>::clear()
{
	if ( !isEmpty() ) {
		node *ptr = _first;
		while (ptr){
			node *next = ptr->next;
			delete ptr;
			ptr = next;
		}
	}
	_size = 0;
	_first=_last=0;
}

template<typename T> T* GeList<T>::add(T new_one)
{
	if (isEmpty())
	{
		_first = new node;
		_first->data=new_one;
		_last=_first;
	}
	else
	{
		node *new_str = new node;
		new_str->previous = _last;
		new_str->data = new_one;
		_last->next=new_str;
		_last=new_str;
	}
	_size++;
	//std::cout << "GeList<T>::add _size = "<< size() <<std::endl;

	return &(this->_last->data);
}

template<typename T> GeList<T> GeList<T>::add_and_ret(T new_one)
{
	if (isEmpty())
	{
	    _first = new node;
	    _first->data=new_one;
        _last=_first;
	}
	else
	{
		node *new_str = new node;
		new_str->previous = _last;
		new_str->data = new_one;
		_last->next=new_str;
		_last=new_str;
	}
	_size++;
//std::cout << "GeList<T>::add _size = "<< size() <<std::endl;
return *this;
}

template<typename T> void GeList<T>::Sort(Ptr l,Ptr r)
{
	if(l==r)
		return;
	Ptr t=l,s=l;
	do
	{
		t++;
		if(t!=r)
		{
			t++;
			s++;
		}
	}
	while(t!=r);
	Sort(l,s);
	Ptr ss=s;
	ss++;
	Sort(ss,r);
	t=l;
	Ptr f=ss,rr=r;
	rr++;
	GeList<T> res;
	while(t!=ss||f!=rr)
	{
		if(t==ss)
		{
			res.add(f.getData());
			f++;
		}
		else
			if(f==rr)
		{
			res.add(t.getData());
			t++;
		}
	else
	{
		if(t.getData()<=f.getData())
		{
			res.add(t.getData());
			t++;
		}
		else
		{
			res.add(f.getData());
			f++;
		}
	}
	}
	t=l;
	for(Ptr i=res.getFirstPtr();i!=res.End();i++)
	{
		t.getData()=i.getData();
		t++;
	}
}
