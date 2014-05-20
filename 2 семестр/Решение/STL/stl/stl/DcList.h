#pragma once

#include <iostream>
#include <list> 
#include <vector> 
#include <fstream>
#include <string> 
#include <algorithm>

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
	vector<ruseng> *_word;
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
		_word = new vector<ruseng>;
	}

	~DcList(){}

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

			ruseng re;
			re.eng = s1; re.rus = s;
			_word->push_back(re);

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
		for (auto it = _word->begin(); it != _word->end(); it++)
			if (it->eng == eng) return it->rus;
		return "<Ничего не найденo..>";
	}

	string findRus(string rus)
	{
		for (auto it = _word->begin(); it != _word->end(); it++)
			if (it->eng == rus) return it->eng;
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

		ruseng re;
		re.eng = eng; re.rus = rus;
		_word->push_back(re);
		cout << "Слово добавлено!" << endl << endl;
	}
	///

	void stl2(char w)
	{
		cout << "Begin stl2..." << endl;
		ofstream f("stl2.txt");
		bool flag = false;
		if (w < 'z')
		for (auto it = _word->begin(); it != _word->end(); it++)
		{
			if (it->eng[0] == w)
			{
				f << it->rus << endl;
				flag = true;
			} else
				if (flag) break;
		}
		cout << "End stl2." << endl;
		f.close();
	}

	void stl3(char w)
	{
		cout << "Begin stl3..." << endl;
		ofstream f("stl3.txt");
		//bool flag = false;
		if (w >'z')
		for (auto it = _word->begin(); it != _word->end(); it++)
		{
			if (it->rus[0] == w)
			{
				//cout << it->rus;
				f << it->eng << endl;
				//flag = true;
			} //else
				//if (flag) break;
		}
		cout << "End stl3." << endl;
		f.close();
	}

	bool eque(string s1, string s2, uint m, uint p)
	{
		if (p > s1. length() || p > s2.length()) return false;

		int n = 0;

		for (int i = p; i < min(s1.length(), s2.length()); i ++)
		{
			if (s1[i] != s2[i]) return false;
			else
			{
				n++;
				if (n == m) return true;
			}
		}

		return false;
	}

	void stl4(string s, uint m, uint p, bool eng = true)
	{
		cout << "Begin stl4..." << endl;
		ofstream f("stl4.txt");
		if (eng)
		for (auto it = _word->begin(); it != _word->end(); it++)
			if (eque(it->eng, s, m,  p)) f << it->rus << endl;
		cout << "End stl4." << endl;

		if (!eng)
		for (auto it = _word->begin(); it != _word->end(); it++)
			if (eque(it->rus, s, m,  p)) f << it->eng << endl;
		cout << "End stl4." << endl;
		f.close();
	}

	void stl5()
	{
		cout << "Begin stl5..." << endl;
		ofstream f("stl5.txt");
		char c = 'a';
		bool firsrt = true;
		
		for (auto it = _word->begin(); it != _word->end(); it++)
		{
			if (it->eng[0] != c || firsrt)
			{
				f << it->rus << endl;
				firsrt = false;
				c = it->eng[0];
			}
		}

		cout << "End stl5." << endl;
		f.close();
	}

	bool str_in_str(const char* main_str, const  char* find_str)
	{
		int i = 0;
		int find_str_size = strlen(find_str);
		int main_str_size = strlen(main_str);
		int result = 0;
		while (i<main_str_size)
		{
			if (main_str[i] == find_str[0])
			{
				int j = 0;
				while (main_str[i] == find_str[j] && i<main_str_size && j<find_str_size)
				{
					i++; j++;
				}
				if (j == find_str_size)
					return true;
			}
			else
				i++;
		}
		return false;
	}

	void stl6(string substr)
	{
		cout << "Begin stl6..." << endl;
		ofstream f("stl6.txt");
		bool firsrt = true;
		
		for (auto it = _word->begin(); it != _word->end(); it++)
		{
			if (str_in_str(it->rus.c_str(), substr.c_str()))
				f << it->eng << endl;
		}

		cout << "End stl6." << endl;
		f.close();
	}

	void stl7()
	{
		cout << "Begin stl7..." << endl;
		ofstream f("stl7.txt");
		bool firsrt = true;
		
		for (auto it = _word->begin(); it != _word->end(); it++)
			f << it->rus << endl;

		cout << "End stl7." << endl;
		f.close();
	}

	void stl8(int l)
	{
		cout << "Begin stl8..." << endl;
		ofstream f("stl8.txt");
		bool firsrt = true;
		
		for (auto it = _word->begin(); it != _word->end(); it++)
			if (it->eng.length() == l) f << it->rus << endl;

		cout << "End stl8." << endl;
		f.close();
	}

	void stl9(string s)
	{
		cout << "Begin stl9..." << endl;
		ofstream f("stl9.txt");
		bool firsrt = true;
		
		for (auto it = _word->begin(); it != _word->end(); it++)
			if (it->rus == s) f << it->eng << endl;

		cout << "End stl9." << endl;
		f.close();
	}

	void stl10(bool chet)
	{
		cout << "Begin stl10..." << endl;
		ofstream f("stl10.txt");
		bool firsrt = true;
		
		for (auto it = _word->begin(); it != _word->end(); it++)
		{
			if (chet)
			{
				if (it->rus.length()%2 == 0) f << it->eng << endl;
			} else
			{
				if (it->rus.length()%2 != 0) f << it->eng << endl;
			}
		}

		cout << "End stl10." << endl;
		f.close();
	}

	void stl11(string s, bool chet)
	{
		cout << "Begin stl11..." << endl;
		ofstream f("stl11.txt");
		bool firsrt = true;
		
		for (auto it = _word->begin(); it != _word->end(); it++)
		{

			for (auto it = _word->begin(); it != _word->end(); it++)
			{
				if (it->rus == s) 
				{
					if (chet)
					{
						if (it->eng.length()%2 == 0) f << it->eng << endl;
					}
					else
					{
						if (it->eng.length()%2 != 0) f << it->eng << endl;
					}
				}
			}
			if (chet)
			{
				if (it->rus.length()%2 == 0) f << it->eng << endl;
			} else
			{
				if (it->rus.length()%2 != 0) f << it->eng << endl;
			}
		}

		cout << "End stl11." << endl;
		f.close();
	}

	void stl12(string s, bool chet)
	{
		cout << "Begin stl12..." << endl;
		ofstream f("stl12.txt");
		bool firsrt = true;
		
		for (auto it = _word->begin(); it != _word->end(); it++)
		{

			for (auto it = _word->begin(); it != _word->end(); it++)
			{
				if (it->rus == s) 
				{
					if (chet)
					{
						if (it->eng.length()%2 == 0) f << it->eng << endl;
					}
					else
					{
						if (it->eng.length()%2 != 0) f << it->eng << endl;
					}
				}
			}
			if (chet)
			{
				if (it->rus.length()%2 == 0) f << it->eng << endl;
			} else
			{
				if (it->rus.length()%2 != 0) f << it->eng << endl;
			}
		}

		cout << "End stl12." << endl;
		f.close();
	}

};