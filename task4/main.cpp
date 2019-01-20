
#include <sstream>
#include <iostream>
#include <fstream>
#include "csv_parser.h"

using namespace csv;

int main(int argc, const char * argv[]) {
	try {
		std::ifstream file("test.csv");
		csv::CSVParser<std::string, int, int, std::string> parser(file, 2);
		for (std::tuple<std::string, int, int, std::string> line : parser) {
			std::cout << line << std::endl;
		}
	}
	catch (CSVParseException& err)
	{
		std::cout << err.what();
	}
  return 0;
}
