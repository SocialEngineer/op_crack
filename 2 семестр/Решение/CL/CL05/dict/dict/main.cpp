#include <iostream>

//#include "DcList.h"
#include "Dictionary.h"
#include <string>

using namespace std;

int main()
{
	setlocale(0, "russian");
	Dictionary d;
	d.load();
	//List2<string> w;

	/*
	w.push("cat");
	w.push("sleep");
	w.push("niggling");
	w.push("������� ����");
	w.push("���������������");*/

	//d.saveTranslation("test.txt", w);
	cout << d.autofind("cat")<<" "<< d.autofind("���������������") <<endl;
	//d.addWordBack("yyyyy", "����");

	//d.addWordWithSort("en-ru_sorted.txt", "babababab", "��������");

	return 0;
}