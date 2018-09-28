#include "Trit.h"

trit Trit::define(int start, int finish) const
//by numbers define trit
{
	if (!start)
	{
		if (!finish)
			return Unknown;
		else
			return True;
	}
	else if (!finish)
		return False;
}

trit Trit::operator&(const Trit& some_trit) const
{
	if (o_trit == False || some_trit.o_trit == False)
		return False;
	if (o_trit == True && some_trit.o_trit == True)
		return True;
	else
		return Unknown;
}

trit Trit::operator|(const Trit& some_trit) const
{
	if (o_trit == False && some_trit.o_trit == False)
		return False;
	if (o_trit == True || some_trit.o_trit == True)
		return True;
	else
		return Unknown;
}

trit Trit::operator~ () const
{
	if (o_trit == True)
		return False;
	if (o_trit == False)
		return True;
	else
		return Unknown;
}

//trit Trit::get(int index, Trit g_trit) const
////get trit from byte
//{
//	int fin, strt;                          
//	//uint temp = trits;
//	for (int i = 0; i <= 6 - index; i++)  //вынести в функцию
//		temp /= 2;
//	strt = temp % 2;
//	temp /= 2;
//	fin = temp % 2;
//	//return Trit::define(strt, fin);
//}

//int Trit::operator=(const trit)
//{
//	
//}
