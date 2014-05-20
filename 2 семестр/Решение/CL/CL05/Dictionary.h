#pragma once

/*
	Dictionary d;
	d.load();

	List2<string> w;
	w.push("cat");
	w.push("sleep");
	w.push("niggling");
	w.push("������� ����");
	w.push("���������������");

	d.saveTranslation("test.txt", w);
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

#include "List.h"
#include "List2.h"

#define DEFAULT_DICIONARY "en-ru_sorted.txt"
#define uint unsigned int

#define MIN(x, y) (x<y?x:y)
#define MIN3(x, y, z) (min(x, y)<min(y, z)?min(x, y):min(y, z))

#define tochr(x)(int(unsigned char(x)))

using namespace std;

class Dictionary
{
	List<string, string> *_data_ruseng;
	List<string, string> *_data_engrus;
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
		_data_ruseng = new List<string, string>();
		_data_engrus = new List<string, string>();
	}

	~Dictionary(){}

	void load(string filename = DEFAULT_DICIONARY, int count = -1)
	{
		cout << "�������� �������, ���������..." << endl;

		_filename = filename;

		fstream f(filename.c_str(), ios_base::in);
		if (!f.is_open())
		{
			cout << "������ ������ �����-�������!";
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
		cout << "������� ��������!" << endl << endl;
	}

	void saveTranslation(string filename, List2<string> &words)
	{
		fstream f(filename.c_str(), ios::out);
		if (!f.is_open())
		{
			cout << "������ ������ �����!";
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

		cout << "��� ����� ���������� � �������� � " << filename << endl;
		f.close();
	}

	void addWordWithSort(string filename, string eng, string rus)
	{
		cout << "������� ���������� �����, ���������..." << endl;

		fstream f(filename.c_str(), ios::in);
		if (!f.is_open())
		{
			cout << "������ ������ �����(��������)!";
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
			if (s1 >= eng)
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
			cout << "������ ������ �����(����������)!";
			return;
		}

		for (int i = 0; i < engrus.length(); i++)
		{
			f2 << engrus[i].key << char(9) << engrus[i].data;
			if (i != engrus.length()-1) f2 << endl;
		}

		f2.close(); 
		

		cout << "����� ���������!" << endl;
	}

	void addWordBack(string eng, string rus)
	{
		cout << "��������� ����� � �������(" << eng << ":" << rus << ")..." << endl;

		fstream f(_filename.c_str(), ios_base::app);
		if (!f.is_open())
		{
			cout << "������ ������ �����-�������!";
			return;
		}

		f << eng << char(9) << rus << endl;

		f.close();

		_data_engrus->add(eng, rus);
		_data_ruseng->add(rus, eng);
		cout << "����� ���������!" << endl << endl;
	}

	string findEng(string eng)
	{
		string *s = _data_engrus->find(eng);
		return s==0?"<������ �� ������o..>":*s;
	}

	string findRus(string rus)
	{
		string *s = _data_ruseng->find(rus);
		return s==0?"<������ �� ������o..>":*s;
	}

	string autofind(string word)
	{
		if (word.length() < 1) return "<������ �� ������o..>";

		if (tochr(word[0]) < tochr('A') || tochr(word[0]) > tochr('�')) return "�������������� ����� ������ ����.";

		if (tochr(word[0]) > tochr('z')) return findRus(word);
		return findEng(word);
	}


};