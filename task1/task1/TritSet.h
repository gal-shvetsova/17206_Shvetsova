#ifndef TRITSET_H
#define TRITSET_H

#include "stdint.h"
enum trit { False = -1, Unknown, True};

class TritSet
{
public:
	TritSet();
	TritSet(const TritSet&);

	TritSet& operator=  (const TritSet&);
	trit  operator[]  (int);

	TritSet operator& (TritSet&) const;
	TritSet operator| (TritSet&) const;
	TritSet operator!();
	TritSet operator^(TritSet&);
	TritSet operator&= (TritSet&);
	TritSet operator|= (TritSet&);
	TritSet operator^=(TritSet&);

	int in_state(TritSet, trit) const;  // count of trits in some state
	void trim(size_t lastIndex); // забыть содержимое от lastIndex и дальш
	size_t length(); // индекс последнего не Unknown трита +1

	~TritSet();
private:
	uint8_t* trits;
	size_t totalsize;
};

#endif