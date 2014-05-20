#include <iostream>
#include "Hash.h"

using namespace std;

int main()
{
	Hash<string, string> tree(HASH_SIZE, stringToHash);

	tree.add("hfs", "dfsdsd");
	tree.add("hfsdfs", "sdfg");
	tree.add("asdhfs", "kkljkl");
	tree.add("hffbvs", "s");
	tree.add("dfhhfs", "jkg");
	tree.add("vhfrs", "rt");

	tree.trace();

	cout << endl << *(tree.find("hffbvs")) << endl;
	return 0;
}