#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <bitset>

using namespace std;


struct Node
{
public:
	int count;
	int ch;
	Node *left, *right;
	Node()
	{
		count = 0;
		left = right = 0;
		ch = 257;
	}

	bool operator==(Node& n)
	{
		return count == n.count;
	}

	bool operator>(Node& n)
	{
		return count > n.count;
	}

	bool operator<(Node& n)
	{
		return count < n.count;
	}

	bool operator>=(Node& n)
	{
		return count >= n.count;
	}

	bool operator<=(Node& n)
	{
		return count <= n.count;
	}
};

void printNodeVector(vector<Node> vc)
{
	for (vector<Node>::iterator it = vc.begin(); it != vc.end(); it++)
		cout << it->ch << " : " << it->count << endl;
}

vector<bool> code;
map<char, vector<bool> > ar;

void createCode(Node* root)
{
	if (root->left != 0)
	{
		code.push_back(0);
		createCode(root->left);
	}

	if (root->right != 0)
	{
		code.push_back(1);
		createCode(root->right);
	}

	if (root->ch < 257) ar.insert(pair<char, vector<bool> >(char(root->ch), code));
	code.pop_back();
}

int main()
{
	//unsigned int table[256];
	vector<Node> table;

	
	for (int i = 0; i < 256; i++)
	{
		Node *p = new Node();
		p->ch = char(i);
		table.push_back(*p);
	} 

	string _filename = "test.txt";

	fstream f(_filename.c_str(), ios::in|ios::binary);
	if (!f.is_open())
	{
		cout << "Ошибка чтения файла!";
		return 0;
	}

	unsigned char c;
	string data = "";

	while (!f.eof())
	{
		f >> c;
		data += c;

		table[c].count ++;
	}

	sort(table.begin(), table.end());
	while (table.size() > 0)
	{
		if (table[0].count != 0) break; 
		table.erase(table.begin());
	}

	int i = 0;
	while (table.size() - i > 1)
	{
		Node *p = new Node();
		p->count = table[i].count + table[i + 1].count;

		p->left = &table[i];
		p->right = &table[i + 1];

		table.push_back(*p);
		sort(table.begin()+i, table.end());
		i += 2;
	}
	
	
	Node* p = &table[table.size()-1];
	//cout << ceil(log(32)/log(2));
	f.close();

	createCode(p);


	fstream f2((_filename+".hfm").c_str(), ios::out|ios::binary);

	unsigned char buf = 0, count = 0;

	for (int i = 0; i < data.length()-1; i++)
	{
		vector<bool> b = ar.find(data[i])->second;
		//int i = 0;
		for (auto it = b.begin(); it != b.end(); it++)
		{
			if (*it)
				buf = buf | (1<<count);
			
			count++;
			if (count == 8)
			{
				cout << int(buf) << endl;
				f2 << buf;
				count = buf = 0;
			}
		}
	}

	f2.close();
	
	getchar();
	return 0;
}