#include "TritSet.h"
#include <iostream>

TritSet::Reference::Reference(const TritSet* other, uint i, uint a)
{
	set = const_cast<TritSet*>(other);
	index_in_number = i;
	index_in_trit_a = a;
}

TritSet::Reference::Reference(TritSet* other, uint i, uint a)
{
	set = other;
	index_in_number = i;
	index_in_trit_a = a;
}

trit TritSet::Reference::get_trit() const
{
		int shift = BITS_FOR_UINT - BITS_FOR_TRIT*(index_in_number + 1);
		return static_cast<trit> (3 & (set->trits[index_in_trit_a] >> shift));
}

TritSet::Reference::operator trit() const
{
	return get_trit();
}

void TritSet::Reference::reallocate()
//reallocate memory for trits array
{
	uint new_size = index_in_trit_a + 1;
	set->trits.resize(new_size);
}

TritSet::Reference TritSet::Reference::operator= (const trit& trit_ref)
{

	if (index_in_trit_a >= set->trits.size())
	{
		if (trit_ref == Unknown)
			return (*this);
		else
			reallocate();
	}

	int shift = BITS_FOR_UINT - (index_in_number + 1) * BITS_FOR_TRIT;
	uint clear_mask = static_cast<uint>(~(3 << shift));
	set->trits[index_in_trit_a] &= clear_mask;
	uint fill_mask = trit_ref << shift;
	set->trits[index_in_trit_a] |= fill_mask;

	set->last_set_trit_i = index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number;
	if (set->last_set_trit_i > set->last_trit_i)
		set->last_trit_i = index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number;;
	return (*this);
}

TritSet::Reference TritSet::Reference::operator= (const Reference& trit_ref)
{
	if (*this == trit_ref)
		return trit_ref;
	trit ref = trit_ref.get_trit();
	if (index_in_trit_a >= set->trits.size())
	{
		if (ref == Unknown)
			return (*this);
		else
			reallocate();
	}

	int shift = BITS_FOR_UINT - (index_in_number + 1) * BITS_FOR_TRIT;
	uint clear_mask = static_cast<uint>(~(3 << shift));
	set->trits[index_in_trit_a] &= clear_mask;
	uint fill_mask = ref << shift;
	set->trits[index_in_trit_a] |= fill_mask;

	set->last_set_trit_i = index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number;
	if (set->last_set_trit_i > set->last_trit_i)
		set->last_trit_i = set->last_trit_i;
	return (*this);
}

std::ostream& operator<<(std::ostream& os, const TritSet::Reference& ref) 
{
	trit t = ref.get_trit();
	if (t == True)
		os << "True";
	else if (t == False)
		os << "False";
	else
		os << "Unknown";
	return os;
}