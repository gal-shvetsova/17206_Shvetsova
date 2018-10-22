#include "Trit.h"

trit operator&(const trit& trit1, const trit& trit2)
{
	if (trit1 == False || trit2 == False)
		return False;
	if (trit1 == True && trit2 == True)
		return True;
	else
		return Unknown;
}

trit operator|(const trit& trit1, const trit& trit2)
{
	if (trit1 == False && trit2 == False)
		return False;
	if (trit1 == True || trit2 == True)
		return True;
	else
		return Unknown;
}

trit operator~(const trit& some_trit)
{
	if (some_trit == True)
		return False;
	if (some_trit == False)
		return True;
	else
		return Unknown;
}

