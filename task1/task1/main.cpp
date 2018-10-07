#include "TritSet.h"
#include "Other.h"
#include <iostream>

int main()
{
	TritSet some(35);
	some[15] = True;  
	some[10] = True;
	some.cut_to_trit(15);
	//for (int i = 0; i < 30; i++)
	//	some[i] = True;
	some[1] = True;
	some[2] = True;
	some[3] = True;
	some[4] = True;
	for (int i = 0; i < 30; i++)
		some[i] = True;
	for (int i = 0; i < 30; i++)
		std::cout << some[i];
	return 0;
}