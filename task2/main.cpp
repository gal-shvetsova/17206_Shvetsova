#include "Context.h"
#include "Exceptions.h"
#include "Creator.h"
#include <iostream>
#include <fstream>
#include "Calculator.h"
int main()
{
	std::ifstream fin;
	std::ofstream fout;
	fin.open("in.txt");
	fout.open("out.txt");
	Calculator calculator;
	calculator.compute(std::cin, std::cout);
	fin.close();
	fout.close();
	return 0;
}