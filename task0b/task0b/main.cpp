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
	string in = argv[1], out = argv[2];
	WordCounter result;
	result.readfile(in);
	result.writeCSV(out);
	return 0;
}