#pragma once

#include <iostream>
#include <map> 
#include <vector> 
#include <fstream>
#include <string> 
#include <algorithm>

using namespace std;

#define DEFAULT_DICIONARY "en-ru_sorted.txt"
#define uint unsigned int
#define tochr(x)(int(unsigned char(x)))

class DcMap
{
	map<string, string> *_re;
	map<string, string> *_er;
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
	DcMap()
	{
		_er = new map<string, string>;
		_re = new map<string, string>;
	}

	~DcMap(){}

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

			_re->insert(pair<string, string>(s, s1));
			_er->insert(pair<string, string>(s1, s));

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

	string findEng(string eng)
	{ 
		//for (auto it = _word->begin(); it != _word->end(); it++)
	///		if (it->eng == eng) return it->rus;
		auto fi = _er->find(eng);
		if (fi != _er->end()) return fi->second;
		return "<Ничего не найденo..>";
	}

	string findRus(string rus)
	{
		auto fi = _re->find(rus);
		if (fi != _re->end()) return fi->second;
		return "<Ничего не найденo..>";
	}

	string autofind(string word)
	{
		if (word.length() < 1) return "<Ничего не найденo..>";

		if (tochr(word[0]) < tochr('A') || tochr(word[0]) > tochr('я')) return "Автоматический поиск только слов.";

		if (tochr(word[0]) > tochr('z')) return findRus(word);
		return findEng(word);
	}

	void saveTranslation(string filename, vector<string> &words)
	{
		fstream f(filename.c_str(), ios::out);
		if (!f.is_open())
		{
			cout << "Ошибка чтения файла!";
			return;
		}

		vector<string> vsort;
		string s;

		for (int i = 0; i < words.size(); i++)
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

		_re->insert(pair<string, string>(rus, eng));
		_er->insert(pair<string, string>(eng, rus));
		cout << "Слово добавлено!" << endl << endl;
	}
};