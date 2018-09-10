#ifndef TRIT_H
#define TRIT_H

#include "stdint.h"
enum trit {Unknown = 0, True, False};

class Trit
{
public:
	trit get(int) const;
	trit define(int, int) const;

	Trit& operator=(const TritSet&);
	trit operator[](int) const;

	Trit operator&(Trit&) const;
	Trit operator|(Trit&) const;
	Trit operator~();
	Trit operator^(Trit&);
	Trit operator&=(Trit&);
	Trit operator|=(Trit&);
	Trit operator^=(Trit&);

private:
	uint8_t trit_4;
};

#endif