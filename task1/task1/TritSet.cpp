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

trit TritSet::operator[](int index) const
{

}