#ifndef TRITSET_H
#define TRITSET_H

#include <vector>
#include "stdint.h"
#include "Trit.h"

typedef unsigned int uint;


class TritSet
{
public:
	TritSet();
	TritSet(const TritSet&);  //copy
	TritSet(uint);  //create vector with some size 

	TritSet& operator=(const TritSet&);
	trit operator[](int) const;

	TritSet operator&(TritSet&) const;
	TritSet operator|(TritSet&) const;
	TritSet operator~();
	TritSet operator^(TritSet&);
	TritSet operator&=(TritSet&);
	TritSet operator|=(TritSet&);
	TritSet operator^=(TritSet&);

	int in_state(TritSet, trit) const;  // count of trits in some state
	void trim(size_t lastIndex); // forget contain of trits starting from lastIndex
	size_t length(); // index of last non-uknown trit +1

	~TritSet();
private:
	std::vector<Trit> trits;
	size_t totalsize;
};

#endif