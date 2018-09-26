#ifndef TRIT_H
#define TRIT_H
#include "Other.h"



class Trit
{
public:
	trit get(int, Trit) const;
	trit define(int, int) const;
	Trit& delete_t(int);
	int operator=(trit);
	//Trit& operator=(trit);
	//trit operator[](int) const;

	Trit operator&(const Trit&) const;
	Trit operator|(const Trit&) const;
	Trit operator~();
	Trit operator^(const Trit&);
	Trit operator&=(const Trit&);
	Trit operator|=(const Trit&);
	Trit operator^=(const Trit&);

private:
	trit o_trit;
};

#endif