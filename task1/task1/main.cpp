#include "TritSet.h"
#include <iostream>
#include <cstddef>
int main()
{
	TritSet t(100);
	TritSet t2(5);
	TritSet t3(2);
	t3 = t2;
	int test;
	trit some = True;
	//TritSet::iterator p = t.begin();
	//for (p; p < t.end; p++)
	std::cout << "false";
	int b = test = 8;

	t[3] = True;
	t[60] = True;
	t[25] = False;
	trit tr = True;
	//if (t[15] == t[25])
	std::unordered_map<trit, uint> n = t.cardinality();
	tr = t.get_trit(60);
	test = t.cardinality(Unknown);
	t[60] = some & t[15];
	t3 = t & t2;
	trit c = t.get_trit(15);
	test = sizeof(uint);
	t[3200] = Unknown;
	
	return 0;
}