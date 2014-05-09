#pragma once

template <typename K, typename V>
class List
{
private:

	struct  Node
	{
	public:
		K key;
		V data;
		Node* next;

		Node()
		{
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

	void add(K key, V val)
	{
		Node* var = new Node();
		var->data = val;
		var->key = key;

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
			_tail->next = _head;
		}
	}

	// есть ли
	bool count(K key)
	{
		if (isEmpty()) return false;

		Node *p = _head, *prev;

		do
		{
			if (p->key == key)
				return true;
			p = p->next;
		} while(p != _head);

		return false;
	}

	V* find(K key)
	{
		if (isEmpty()) return 0;

		Node *p = _head, *prev;

		do
		{
			if (p->key == key)
				return &(p->data);
			p = p->next;
		} while(p != _head);

		return 0;
	}

	void remove(K key)
	{
		if (isEmpty()) return;

		Node *p = _head, *_old = _tail;

		do
		{
			if (p->key == key)
			{
				old->next = p->next;
				delete p;
				return;
			}
			_old = p;
			p = p->next;
		} while(p != _head);
	}

	bool trace()
	{
		Node *p = _head;

		if (isEmpty()) return false;

		do
		{
			cout << p->key << " : " << p->data << endl;
			p = p->next;
		} while(p != _head);

		return true;
	}
	
};
