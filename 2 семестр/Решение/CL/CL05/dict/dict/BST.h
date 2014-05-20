#pragma once

#include <iostream>
#include <string>

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

	class track
 {
     Node *current;
 public :
	 friend class BST;
	 track(){current=0;};
	 track(track &tr){current=tr.current;}
	 bool canMove(Node *next){return next; };
	
	 V getData()
	 {
		return current->value;
	 }

	 track& operator++ (){if(current) next(); return *this;}; // Перемещает к следующему элементу

	 bool operator !=(track it)
		{
			if(current->parent == it.current)
				return 0;
			return 1;
		};

	 void previous()
	{   node *current_;
		current_ = current;
	if (canMove(current->left)){ 
	current=current->left;
	while(canMove(current_->right)) {
		 current_=current_->right;
	}
	}
	else{
		while(current->parent->k>current_->k){
			current_=curren_->parent;
			if (!canMove(current_)) {
			std::cout << current->v << curren->k <<"   This is min element";
			return;
		    };
		}
	    current=current_;
     };
	};

	void next()
	{  
		Node *current_;
		current_ = current;  
		if(canMove(current_->right)){ 
		current_=current_->right;
		while(canMove(current_->left)) 
		{
		 current_=current_->left;
		}
	current=current_;
	//return current;
	}
	else {
		while(current_->parent->key < current_->key){
			current_=current_->parent;
		 if (!canMove(current_)) {
		//	 std::cout << current->v << current->k <<"   This is max element";
			 return;
		 }
		 }
		 current=current_->parent;
	 };

	 };
	 
 };

	track getFirstPtr()  // return min 
 {
 track firstTrack;
 firstTrack.current = _root;
	 
	while(firstTrack.canMove(firstTrack.current->left))
		firstTrack.current=firstTrack.current->left;	

 return firstTrack;
 };

track End()
{
	track lastTrack;
	lastTrack.current = _root;
	while(lastTrack.canMove(lastTrack.current->right))
		lastTrack.current = lastTrack.current->right;

	return lastTrack;
}

	
private:
	Node* _root;
	Node* _end;
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

		return leftMost(beg->left);
	}

	void nodeRemove(Node* nd)
	{
		if (nd == 0) return;

		// нет детей
		if (!nd->left && !nd->right)
		{

			if (nd->parent->key < nd->key) nd->parent->right = 0;
			else nd->parent->left = 0;

			delete nd;
			return;
		}

		// имеем левого ребенка
		if (nd->left && !nd->right)
		{
			if (nd->parent->key < nd->key) nd->parent->right = nd->left;
			else nd->parent->left = nd->left;

			nd->left->parent = nd->parent;
			delete nd;
			return;
		}

		// имеем правого ребенка
		if (!nd->left && nd->right)
		{
			if (nd->parent->key < nd->key) nd->parent->right = nd->right;
			else nd->parent->left = nd->right;

			nd->right->parent = nd->parent;
			delete nd;
			return;
		}

		// имеем всех двух детей
		Node* rght = rightMost(nd->left);

	//	cout << rght->key << " : " << endl;

		nd->key = rght->key;
		nd->value = rght->value;

		nodeRemove(rght);
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
