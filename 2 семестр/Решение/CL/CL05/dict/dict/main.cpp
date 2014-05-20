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
	w.push("тушеное мясо");
	w.push("биметаллический");*/

	//d.saveTranslation("test.txt", w);
	cout << d.autofind("cat")<<" "<< d.autofind("биметаллический") <<endl;
	//d.addWordBack("yyyyy", "орол");

	//d.addWordWithSort("en-ru_sorted.txt", "babababab", "бабабаба");

	return 0;
}