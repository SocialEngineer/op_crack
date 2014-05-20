#pragma once

/*
	Dictionary d;
	d.load();

	List2<string> w;
	w.push("cat");
	w.push("sleep");
	w.push("niggling");
	w.push("тушеное мясо");
	w.push("биметаллический");

	d.saveTranslation("test.txt", w);
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#define DEFAULT_DICIONARY "en-ru_sorted.txt"
#define uint unsigned int

#define MIN(x, y) (x<y?x:y)
#define MIN3(x, y, z) (min(x, y)<min(y, z)?min(x, y):min(y, z))

#define tochr(x)(int(unsigned char(x)))

using namespace std;

class Dictionary_1
{
	map<string, string> *_data_ruseng;
	map<string, string> *_data_engrus;
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
	Dictionary_1()
	{
		setlocale(LC_ALL, "Russian");
		_data_ruseng = new map<string, string>;
		_data_engrus = new map<string, string>;
	}

	~Dictionary_1(){}

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
			_data_engrus->insert(pair<string, string>(s1, s)); //add(s1, s);
			_data_ruseng->insert(pair<string, string>(s, s1));

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

		map<string, string> engrus;

		while (!f.eof())
		{
			getline(f, s);
			k = findSpaceTab(s);
			s1 = upperCase(s.substr(0, k));
			s = upperCase(s.substr(k+1, s.length()-k-1));
			if (s1 >= eng)
			{
				engrus.insert(pair<string, string>(eng, rus));
				flag = 1;
			}

			engrus.insert(pair<string, string>(s1, s));
		}

		if (!flag) engrus.insert(pair<string, string>(eng, rus));


		f.close(); 
		
		fstream f2(filename.c_str(), ios::out|ios::trunc);
		if (!f2.is_open())
		{
			cout << "Ошибка чтения файла(сохранение)!";
			return;
		}

		for (auto it = engrus.begin(); it != engrus.end(); it++)
		{
			f2 << it->first << char(9) << it->second << endl;
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

		_data_engrus->insert(pair<string, string>(eng, rus));
		_data_ruseng->insert(pair<string, string>(rus, eng));
		cout << "Слово добавлено!" << endl << endl;
	}

	string findEng(string eng)
	{
		string *s = 0;
		auto it = _data_engrus->find(eng);
		if(it != _data_engrus->end()) *s = it->second;
		return s==0?"<Ничего не найденo..>":*s;
	}

	string findRus(string rus)
	{
		string *s;
		*s = (_data_ruseng->find(rus))->second;
		return s==0?"<Ничего не найденo..>":*s;
	}

	string autofind(string word)
	{
		if (word.length() < 1) return "<Ничего не найденo..>";

		if (tochr(word[0]) < tochr('A') || tochr(word[0]) > tochr('я')) return "Автоматический поиск только слов.";

		if (tochr(word[0]) > tochr('z')) return findRus(word);
		return findEng(word);
	}


};