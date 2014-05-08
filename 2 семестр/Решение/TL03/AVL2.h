#pragma once
#include <math.h>
#include <vector>

#define uint unsigned int;

template <typename K, typename V>
class AVL2
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

	AVL2()
	{
		_root = 0;
		_count = 0;
	}

	~AVL2(void) {}

	bool isEmpty()
	{
		return _root == 0;
	}

	bool balance( Node* nd )
	{
		int bf = height(nd->right) - height(nd->left);
		if (abs(bf) == 2)
		{
			Node* child;
			if (bf > 0) child = nd->right;
			else child = nd->left;

			int bf_c = height(child->right) - height(child->left);

			if (bf > 0 && bf_c > 0) // left
				child = leftRotation(child); else
			if (bf < 0 && bf_c < 0) // right
				child = rightRotation(child); else
			if (bf > 0 && bf_c < 0) // right-left
				child = leftRotation(rightRotation(child->left)); else
			if (bf < 0 && bf_c > 0) // left-right
				child = rightRotation(leftRotation(child->right));

			return true;
		}

		return false;
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
				if (current->key == key) 
				{
					current->value = value;
					return;
				}

				parent = current;
				if (nd->key > current->key) current = current->right;
				else current = current->left;
			}

			if (nd->key > parent->key) parent->right = nd;
			else parent->left = nd;
			nd->parent = parent;

			do // балансируем, если надо
			{
				if (balance(nd)) break;
				nd = nd->parent;
			} while (nd);

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

		Node* d = nodeRemove(find(key));
		Node* nd = d->parent;
		delete d;

		do // балансируем, если надо
		{
			if (balance(nd)) break;
			nd = nd->parent;
		} while (nd);
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

	void widthTrace()
	{
		std::vector<Node*> node;
		int k = 0, t = 0;
		node.push_back(_root);

		while (k != node.size())
		{
			if (node[k]->left) 
					node.push_back(node[k]->left);
			if (node[k]->right) 
					node.push_back(node[k]->right);
			k++;

			if ( t == floor(log(k)/log(2)) )
			{
				t++;
				cout << endl;
			}

			cout << node[k-1]->key << "  ";
		}
		node.clear();
	}
	
private:
	Node* _root;
	int _count;

	Node* leftRotation(Node* p)
	{
		if (!p) return 0;
		Node* pp = p->parent;

		if (pp == _root) _root = p;

		p->parent = pp->parent;
		pp->parent = p;
		if (p->parent)
			if ( p->parent->key < p->key  ) p->parent->right = p;
			else p->parent->left = p;
		pp->right = p->left;
		p->left = pp;

		return p;
	}

	Node* rightRotation(Node* p)
	{
		if (!p) return 0;
		Node* pp = p->parent;

		if (pp == _root) _root = p;

		p->parent = pp->parent;
		pp->parent = p;
		if (p->parent)
			if ( p->parent->key < p->key  ) p->parent->right = p;
			else p->parent->left = p;
		pp->left = p->right;
		p->right = pp;

		return p;
	}

	int height(Node* p)
	{
		if (!p) return -1;
		return max(height(p->left), height(p->right)) + 1;
	}

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

		return leftMost(beg->left);
	}

	Node* nodeRemove(Node* nd)
	{
		if (nd == 0) return 0;

		// нет детей
		if (!nd->left && !nd->right)
		{

			if (nd->parent->key < nd->key) nd->parent->right = 0;
			else nd->parent->left = 0;
			
			return nd;
		}

		// имеем левого ребенка
		if (nd->left && !nd->right)
		{
			if (nd->parent->key < nd->key) nd->parent->right = nd->left;
			else nd->parent->left = nd->left;

			nd->left->parent = nd->parent;
			return nd;
		}

		// имеем правого ребенка
		if (!nd->left && nd->right)
		{
			if (nd->parent->key < nd->key) nd->parent->right = nd->right;
			else nd->parent->left = nd->right;

			nd->right->parent = nd->parent;
			return nd;
		}

		// имеем всех двух детей
		Node* rght = rightMost(nd->left);

		nd->key = rght->key;
		nd->value = rght->value;

		return nodeRemove(rght);
	}

	void traceNode(Node* p = 0, int level = 0)
	{
		if(p)
		{
			traceNode(p->left, level + 1);
			for(int i = 0; i < level; i++) cout << "   ";
				cout << p->key << endl;
			traceNode(p->right, level + 1);
		}
	}
};