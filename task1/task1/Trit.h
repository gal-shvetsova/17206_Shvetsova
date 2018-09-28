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

	trit operator&(const Trit&) const;
	trit operator|(const Trit&) const;
	trit operator~() const;
	trit operator^(const Trit&);
	trit operator&=(const Trit&);
	trit operator|=(const Trit&);
	trit operator^=(const Trit&);

private:
	trit o_trit;
};

#endif