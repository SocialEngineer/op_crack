#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "List2.h"

using namespace std;

#define DEFAULT_DICIONARY "en-ru_sorted.txt"
#define uint unsigned int
#define tochr(x)(int(unsigned char(x)))

struct ruseng
{
	string rus;
	string eng;
};

class DcList
{
	List2<ruseng> *_word;
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
	DcList()
	{
		_word = new List2<ruseng>;
	}

	~DcList(){}

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

			ruseng re;
			re.eng = s1; re.rus = s;
			_word->push(re);

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

	string findEng(string eng)
	{

		for(int i = 0; i < _word->length(); i++)
			if ((*_word)[i].eng == eng) return (*_word)[i].rus;
		return "<������ �� ������o..>";
	}

	string findRus(string rus)
	{
		for(int i = 0; i < _word->length(); i++)
			if ((*_word)[i].rus == rus) return (*_word)[i].eng;
		return "<������ �� ������o..>";
	}

	string autofind(string word)
	{
		if (word.length() < 1) return "<������ �� ������o..>";

		if (tochr(word[0]) < tochr('A') || tochr(word[0]) > tochr('�')) return "�������������� ����� ������ ����.";

		if (tochr(word[0]) > tochr('z')) return findRus(word);
		return findEng(word);
	}

	void saveTranslation(string filename, vector<string> &words)
	{
		fstream f(filename.c_str(), ios::out);
		if (!f.is_open())
		{
			cout << "������ ������ �����!";
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

		cout << "��� ����� ���������� � �������� � " << filename << endl;
		f.close();
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

		ruseng re;
		re.eng = eng; re.rus = rus;
		_word->push(re);
		cout << "����� ���������!" << endl << endl;
	}

};
