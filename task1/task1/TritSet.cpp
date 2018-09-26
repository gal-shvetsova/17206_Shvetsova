#include "TritSet.h"

TritSet::TritSet()
{
	trits.resize(0);
	totalsize = 0;
}

TritSet::TritSet(const TritSet& obj)
{
	totalsize = obj.totalsize;
	trits.resize(totalsize - 1);
	for (int i = 0; i < totalsize; i++)
		trits[i] = obj.trits[i];
}

TritSet::TritSet(uint size)
{
	trits.resize(size - 1);
	totalsize = size;
}

TritSet::Reference TritSet::operator[](const int& index) const
{
	size_t array_index = index % (BITS_FOR_UINT / BITS_FOR_TRIT),  //index in number 
		int_index = (index * BITS_FOR_TRIT / BITS_FOR_UINT); // index in array of int
	Reference ref(this, array_index, int_index);
	return ref;
}

