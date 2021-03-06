#ifndef MAKEDICT_H
#define MAKEDICT_H

#include <string>
#include <map>

using std::string;
using std::map;

bool Is_Separator(char sym);

class WordCounter
{
private:
	int total_size = 0;
	map<string, int> dict;
	void addwords(string&);
	void WordCounter::sort(std::multimap<int, string>& mp);
public:
	bool readfile(string&);
	bool writeCSV(string&) ;
};

#endif