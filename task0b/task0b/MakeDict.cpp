#include "MakeDict.h"

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

map<string, int> Add_Words(string tmp, map<string, int> dict, int& count)
{
	int j = 0;
	for (int i = 0; i < tmp.length(); i++)     
	{
		if (Is_Separator(tmp[i]))
		{
			dict[tmp.substr(j, i - j)]++;
			j = i + 1;
			count++;
		}

	}
	if (j < tmp.length())
	{
		dict[tmp.substr(j, tmp.length() - j)]++;
		count++;
	}
	return dict;
}