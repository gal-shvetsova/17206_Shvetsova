#include "MakeDict.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Not enough arguements" << "\n";
		return 0;
	}
	string in = argv[1], out = argv[2];
	WordCounter result;
	if (result.readfile(in))
	{
		if (!result.writeCSV(out))
			std::cout << "out-file oppening error" << "\n";
	}
	else std::cout << "in-file oppening error" << "\n";
	return 0;
}