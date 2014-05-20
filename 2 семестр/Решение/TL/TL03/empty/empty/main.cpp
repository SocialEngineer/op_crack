#include <iostream>
#include <string>
#include "AVL2.h"

using namespace std;

int main()
{
	AVL2<int, string> tree;

	tree.insert(3, "dfsdsd");
	tree.insert(1, "sdfg");
	tree.insert(8, "kkljkl");
	tree.insert(4, "s");
	tree.insert(0, "jkg");
	tree.insert(3, "rt");

	tree.trace();

	cout << endl << (tree.find(8)->value) << endl;
	return 0;
}