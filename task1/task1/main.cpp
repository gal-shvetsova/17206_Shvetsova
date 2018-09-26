#include "TritSet.h"
#include <iostream>
#include <cstddef>
int main()
{
	TritSet t(100);
	
	int b = 0x01 << 30;
	t[15] = False;
	t[60] = True;
	t[60] = t[30];
	trit c = t.get_trit(15);
	bool a = (t[60] == c);
	return 0;
}