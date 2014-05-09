#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Hash.h"

#define DEFAULT_DICIONARY "en-ru_sorted.txt"
#define uint unsigned int

#define MIN(x, y) (x<y?x:y)
#define MIN3(x, y, z) (min(x, y)<min(y, z)?min(x, y):min(y, z))

using namespace std;

class Dictionary
{
	Hash<string, string> *_data_ruseng;
	Hash<string, string> *_data_engrus;
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
		_data_ruseng = new Hash<string, string>(HASH_SIZE, stringToHash);
		_data_engrus = new Hash<string, string>(HASH_SIZE, stringToHash);
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
			_data_engrus->add(s1, s);
			_data_ruseng->add(s, s1);

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

	void addWord(string eng, string rus)
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

		_data_engrus->add(eng, rus);
		_data_ruseng->add(rus, eng);
		cout << "Слово добавлено!" << endl << endl;
	}

	string findEng(string eng)
	{
		string *s = _data_engrus->find(eng);
		return s==0?"<Ничего не найденo..>":*s;
	}

	string findRus(string rus)
	{
		string *s = _data_ruseng->find(rus);
		return s==0?"<Ничего не найденo..>":*s;
	}

	string autofind(string word)
	{
		if (word.length() < 1) return "<Ничего не найденo..>";

		if (word[0] < 'A' || word[0] > 'я') return "Автоматический поиск только слов.";
		if ( (word[0] > 'z' || word[0] < 'А') && (word[0] != 'ё' || word[0] != 'Ё')) return "Автоматический поиск только слов.";

		if (word[0] > 'z') return findRus(word);
		return findEng(word);
	}


};