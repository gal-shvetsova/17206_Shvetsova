#include "Context.h"
#include "Exceptions.h"
#include "Creator.h"
#include <iostream>
#include <fstream>
int main()
{
	std::ifstream fin;
	std::ofstream fout;
	fin.open("in.txt");
	fout.open("out.txt");
	Context context;
	context.compute(std::cin, std::cout);
	fin.close();
	fout.close();
	return 0;
}