#pragma once


template <typename V>
 class List3
 {
 public:

	struct Node       //Структура являющаяся звеном списка
	{
		V data;    
		Node *next, *prev;
	};

	List3<V>& operator=(List3<V> val)
	{
		clear();
		int s = val.length(), i = 0;
		while(i < s) 
		{
			push(val[i]);
			i++;
		}
			
		return *this; 
	}

	V& operator[](int i)
	{
		Node *p  = _head;
		
		if (i < 0 || i > _length) abort();
		if (i < 0 || i > _length) abort();

		for (int k = 0; k < i; k++)
			p = p->next;
	
		return p->data;
	}

     List3():_head(NULL),_tail(NULL)
	 {
		 _length = 0;
	 }

     ~List3()
	 {
		clear();
	 }

	 void clear()
	 {
		_head = _tail = 0; 
		_length = 0;
	 }

     void push(V val)
	 {
		Node *temp = new Node;
		temp->next = 0;  
		temp->data = val;
 
		if (!isEmpty()) 
		{
			temp->prev = _tail;
			_tail->next = temp; 
			_tail = temp;
		}
		else 
		{
			temp->prev = 0;
			_head = _tail = temp; 
		}
		_length++;
	 }

	bool isEmpty()
	{
		return _head == 0 || _length == 0;
	}

	int length()
	{
	    return _length;
	}

	bool trace()
	{
		Node *p = _head;

		if (isEmpty()) return false;

		do
		{
			cout << p->data << " ";
			p = p->next;
		} while(p);

		return true;
	}

 private:
	 Node *_head, *_tail; 
	 int _length;
 };