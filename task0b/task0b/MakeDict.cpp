#include "MakeDict.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;

bool Is_Separator(char sym)
{
	if (sym >= '0' && sym <= '9')
		return false;
	if (sym >= 'A' && sym <= 'Z')
		return false;
	if (sym >= 'a' && sym <= 'z')
		return false;
	return true;
}

void WordCounter::addwords(string& to_read)
{
	int j = 0;
	for (int i = 0; i < to_read.length(); i++)     
	{
		if (Is_Separator(to_read[i]))
		{
			dict[to_read.substr(j, i - j)]++;
			j = i + 1;
			total_size++;
		}

	}
	if (j < to_read.length())
	{
		dict[to_read.substr(j, to_read.length() - j)]++;
		total_size++;
	}
}

bool WordCounter::readfile(string& in_name)
{
	ifstream fin;
	fin.open(in_name);
	if (!fin)
		return false;
	string temp;
	while (std::getline(fin, temp, '\n'))
		addwords(temp); 
	fin.close();
	return true;
}

bool WordCounter::writeCSV(string& out_name) 
{
	std::multimap <int, string> mp;
	sort(mp);
	ofstream fout;
	fout.open(out_name);
	if (!fout)
		return false;
	std::multimap <int, string>::iterator cur = mp.end();
	cur--;
	for (; cur != mp.begin(); cur--)
		fout << cur->second << "," << cur->first << "," << int(float(cur->first) / total_size * 100) << "\n";
	fout << cur->second << "," << cur->first << "," << int(float(cur->first) / total_size * 100) << "\n";
	fout.close();
	return true;
}

void WordCounter::sort(std::multimap<int, string>& mp) 
{
	std::multimap <string, int>::iterator cur;
	for (cur = dict.begin(); cur != dict.end(); cur++)
		mp.insert(std::pair<int, string>(cur->second, cur->first));
}