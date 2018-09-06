#include "MakeDict.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Not enough arguements" << "\n";
		return 0;
	}

	string in, out;
	in = argv[1];
	out = argv[2];
	
	ifstream fin;
	ofstream fout;
	fin.open(in);
	fout.open(out);

	string temp;
	map <string, int> dict;
	int cnt = 0;
	int &count = cnt;
	map <string, int>::iterator cur;

	while(std::getline(fin, temp, '\n'))
		dict = Add_Words(temp, dict, count);

	for (cur = dict.begin(); cur != dict.end(); cur++)
		fout << cur->first << "," << cur->second << "," << float(cur->second) / count * 100 << "\n";

	fout.close();
	fin.close();

	return 0;
}