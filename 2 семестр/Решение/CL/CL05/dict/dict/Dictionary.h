#pragma once


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

#include "List.h"
#include "List2.h"
#include "BST.h"

#include "GeList.h"
#include "GeArray.h"

#define DEFAULT_DICIONARY "en-ru_sorted.txt"
#define uint unsigned int

#define MIN(x, y) (x<y?x:y)
#define MIN3(x, y, z) (min(x, y)<min(y, z)?min(x, y):min(y, z))

#define tochr(x)(int(unsigned char(x)))

using namespace std;

#define LIST

struct ruseng
{
	string rus;
	string eng;
};

class Dictionary
{
#ifdef LIST
	GeList<ruseng> *_word;
#endif
#ifdef ARRAY
	GeArray<ruseng> *_word;
#endif
#ifdef BST
	BST<string, string> *_data_ruseng; //
	BST<string, string> *_data_engrus; // 
#endif
	string _filename;

	int findSpaceTab(string s)
	{
		for (uint i = 0; i < s.length(); i ++)
			if ( s[i] == 32 || s[i] == 9 ) return i;
		return -1;
	}

	string upperCase(string s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == 32) continue;

			if ((s[i] > 64 && s[i] < 91) ||
				(s[i] > 191 && s[i] < 224))
				s[i] += 32;
			if (s[i] == 168) s[i] = 184;
		}
		return s;
	}

public:
	Dictionary()
	{
		setlocale(LC_ALL, "Russian");
#ifdef LIST
		_word = new GeList<ruseng>;
#endif
#ifdef ARRAY
		_word = new GeArray<ruseng>(50);
#endif
#ifdef BST
		_data_ruseng = new BST<string, string>();
		_data_engrus = new BST<string, string>();
#endif
	}

	~Dictionary(){}

	void load(string filename = DEFAULT_DICIONARY, int count = -1)
	{
		cout << "Загрузка словаря, подождите..." << endl;

		_filename = filename;

		fstream f(filename.c_str(), ios_base::in);
		if (!f.is_open())
		{
			cout << "Ошибка чтения файла-словаря!";
			return;
		}

		string s, s1;
		int k;

		while (!f.eof())
		{
			getline(f, s);
			k = findSpaceTab(s);
			s1 = upperCase(s.substr(0, k));
			s = upperCase(s.substr(k+1, s.length()-k));

			//list
#if defined(LIST) || defined(ARRAY)
			ruseng re;
			re.eng = s1; re.rus = s;
			_word->add(re);

			//cout << _word->_size << endl;
#endif
#ifdef BST	
			//bst
			_data_engrus->insert(s1, s);
			_data_ruseng->insert(s, s1);
#endif

			if (count != -1)
			{
				count --;
				if (count <= 0) break;
			}
			//cout << s << ":"<<s1 << endl;
		}

		f.close();
		cout << "Словарь загружен!" << endl << endl;
	}

	void saveTranslation(string filename, List2<string> &words)
	{
		fstream f(filename.c_str(), ios::out);
		if (!f.is_open())
		{
			cout << "Ошибка чтения файла!";
			return;
		}

		vector<string> vsort;
		string s;

		for (int i = 0; i < words.length(); i++)
		{
			vsort.push_back(autofind(words[i]));
		}

		sort(vsort.begin(), vsort.end());  

		for (int i = 0; i < vsort.size(); i++)
		{
			//cout << words[i] << endl;
			f << vsort[i];
			if (i != vsort.size()-1) f << endl;
		}

		cout << "Все слова переведены и записаны в " << filename << endl;
		f.close();
	}

	void addWordWithSort(string filename, string eng, string rus)
	{
		cout << "Открыие указанного файла, подождите..." << endl;

		fstream f(filename.c_str(), ios::in);
		if (!f.is_open())
		{
			cout << "Ошибка чтения файла(загрузка)!";
			return;
		}

		string s, s1;
		int k, flag = 0;

		List<string, string> engrus;

		while (!f.eof())
		{
			getline(f, s);
			k = findSpaceTab(s);
			s1 = upperCase(s.substr(0, k));
			s = upperCase(s.substr(k+1, s.length()-k-1));
			if (s1 >= eng && flag == 0)
			{
				engrus.add(eng, rus);
				flag = 1;
			}

			engrus.add(s1, s);
		}

		if (!flag) engrus.add(eng, rus);


		f.close(); 
		
		fstream f2(filename.c_str(), ios::out|ios::trunc);
		if (!f2.is_open())
		{
			cout << "Ошибка чтения файла(сохранение)!";
			return;
		}

		for (int i = 0; i < engrus.length(); i++)
		{
			f2 << engrus[i].key << char(9) << engrus[i].data;
			if (i != engrus.length()-1) f2 << endl;
		}

		f2.close(); 
		

		cout << "Слово добавлено!" << endl;
	}

	void addWordBack(string eng, string rus)
	{
		cout << "Добавляем слово в словарь(" << eng << ":" << rus << ")..." << endl;

		fstream f(_filename.c_str(), ios_base::app);
		if (!f.is_open())
		{
			cout << "Ошибка чтения файла-словаря!";
			return;
		}

		f << eng << char(9) << rus << endl;

		f.close();

		//list 
#if defined(LIST) || defined(ARRAY)
			ruseng re;
			re.eng = eng; re.rus = rus;
			_word->add(re);
#endif
#ifdef BST
		//bst
		_data_engrus->insert(eng, rus);
		_data_ruseng->insert(rus, eng);
#endif

		cout << "Слово добавлено!" << endl << endl;
	}

	string findEng(string eng)
	{
		//list
#if defined(LIST) || defined(ARRAY)
		for(auto it = _word->getFirstPtr();  it != _word->End(); it++)
			if (it.getData().eng == eng) return it.getData().rus;
#endif

#ifdef BST
		//bst
		BST<string, string>::Node* n =  _data_engrus->find(eng);
		if (n) return  n->value;
#endif
		return "<Ничего не найденo..>";
	}

	string findRus(string rus)
	{
		//list
#if defined(LIST) || defined(ARRAY)
		for(auto it = _word->getFirstPtr();  it != _word->End(); it++)
			if (it.getData().rus == rus) return it.getData().eng;
#endif
#ifdef BST
		//bst
		BST<string, string>::Node* n =  _data_ruseng->find(rus);
		if (n) return  n->value;
#endif
		return "<Ничего не найденo..>";
	}

	string autofind(string word)
	{
		if (word.length() < 1) return "<Ничего не найденo..>";

		if (tochr(word[0]) < tochr('A') || tochr(word[0]) > tochr('я')) return "Автоматический поиск только слов.";

		if (tochr(word[0]) > tochr('z')) return findRus(word);
		return findEng(word);
	}


};