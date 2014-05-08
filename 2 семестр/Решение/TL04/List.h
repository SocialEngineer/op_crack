#pragma once

template <typename T>
class List
{
private:

	struct  Node
	{
	public:
		T data;
		Node* next;

		Node()
		{
			//data = 0;
			next = 0;
		}
	};

	Node *_head;
	Node *_tail;
	int _length;
public:
	List()
	{
		_head = _tail = 0;
		_length = 0;
	}

	~List()
	{
		clear();
	}

	void clear()
	{
		if (!_length) return;

		Node *p  = _head, *v;
		while(p->next) 
		{
			v = p->next;
			delete p;
			p = v;
			_length--;
		}
	}

	int length()
	{
	    return _length;
	}

	bool isEmpty()
	{
		return _head == 0;
	}

	void add(T val)
	{
		Node* var = new Node();
		var->data = val;

		_length++;

		if (isEmpty())
		{
			_head = var;
			_tail = _head;
			_head->next = _tail;
		} else
		{
			_tail->next = var;
			_tail = var;
		}
	}

	// есть ли
	bool count(T val)
	{
		Node *p = _head, *prev;

		do
		{
			if (p->data == val)
				return true;
			p = p->next;
		} while(p != _head);

		return false;
	}

	T find(T val)
	{
		Node *p = _head;

		do
		{
			if (p->data == val)
				return p->data;
			p = p->next;
		} while(p != _head);

		return false;
	}

	void remove(T val)
	{
		Node *p = _head, *_old = _tail;

		do
		{
			if (p->data == val)
			{
				old->next = p->next;
				delete p;
				return;
			}
			_old = p;
			p = p->next;
		} while(p != _head);

		return false;
	}
	
};
