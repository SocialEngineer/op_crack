#pragma once

#include <iostream>

template <typename K, typename V>
class BST
{
public:
	typedef struct Node
	{
		K key;
		V value;
		Node* parent;
		Node* left;
		Node* right;
		Node(K key, V value)
		{
			this->key = key;
			this->value = value;
			parent = 0;
			left = 0;
			right = 0;
		}
	};

	BST()
	{
		_root = 0;
		_count = 0;
	}

	~BST(void) {}

	bool isEmpty()
	{
		return _root == 0;
	}

	void insert(K key, V value)
	{
		Node *nd = new Node(key, value);

		if (isEmpty()) 
			_root = nd;
		else
		{
			Node *current, *parent;
			current = _root;
			parent = 0;

			while (current)
			{
				parent = current;
				if (nd->key > current->key) current = current->right;
				else current = current->left;
			}

			if (nd->key > parent->key) parent->right = nd;
			else parent->left = nd;
			nd->parent = parent;
		}
		_count++;
	}

	Node* find(K key)
	{
		if (isEmpty()) return 0;
		return findOfRoot(key, _root);
	}

	void remove(K key)
	{
		if (isEmpty()) return;

		nodeRemove(find(key));
	}

	Node* root()
	{
		return _root;
	}

	void trace()
	{
		traceNode(_root);
		std::cout << std::endl;
	}
	
private:
	Node* _root;
	int _count;

	Node* findOfRoot(K key, Node *beg)
	{
		if (beg == 0) return 0;
		if (key == beg->key) return beg;

		Node *f = findOfRoot(key, beg->left);
		if (f == 0) return findOfRoot(key, beg->right);
		else return f;
	}

	Node* rightMost(Node *beg)
	{
		if (beg == 0) return 0;
		if (!beg->right) return beg;

		return rightMost(beg->right);
	}

	Node* leftMost(Node *beg)
	{
		if (beg == 0) return 0;
		if (!beg->left) return beg;

		return lefttMost(beg->left);
	}

	void nodeRemove(Node* nd)
	{
		if (nd == 0) return;

		// нет детей
		if (((int)nd->left == 0) && ((int)nd->right == 0))
		{
			//nd->parent = 0;
			if (nd->parent->left == nd)
				nd->parent->left = 0;
			else nd->parent->right = 0;

			delete nd;
			return;
		}

		// имеем левого ребенка
		if (((int)nd->left == 1) && ((int)nd->right == 0))
		{
			//nd->parent = nd->left;
			if (nd->parent->left == nd)
				nd->parent->left = nd->left;
			else nd->parent->right = nd->left;

			delete nd;
			return;
		}

		// имеем правого ребенка
		if (((int)nd->left) == 0 && ((int)nd->right == 1))
		{
			//nd->parent = nd->right;
			if (nd->parent->left == nd)
				nd->parent->left = nd->right;
			else nd->parent->right = nd->right;

			delete nd;
			return;
		}

		// имеем всех двух детей
		Node* rght = rightMost(nd);

		nd->key = rght->key;
		nd->value = rght->value;

		nodeRemove(rght);
	}

	void traceNode(Node* node = 0)
	{
		if (!node) return;

		std::cout << "(key: " << node->key << ", value = " << node->value << ") : ";
		traceNode(node->left);
		traceNode(node->right);
	}
};

