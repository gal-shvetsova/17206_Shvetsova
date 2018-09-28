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

void TritSet::Reference::reallocate()
//reallocate memory for trits array
{
	uint new_size = index_in_trit_a + 1;
	set->trits.resize(new_size);
}

bool TritSet::Reference::operator==(const TritSet::Reference& trit_ref) const
{
	trit trit1 = trit_ref.set->get_trit((trit_ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint) * BITS_FOR_TRIT + trit_ref.index_in_number));
	trit trit2 = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint) * BITS_FOR_TRIT + index_in_number));
	return trit1 == trit2;
}

bool operator==(const TritSet::Reference& ref, const trit& trit_v)
{
	trit t = ref.set->get_trit((ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + ref.index_in_number));
	return t == trit_v;
}

bool TritSet::Reference::operator!=(const Reference trit_ref) const
{
	trit trit1 = trit_ref.set->get_trit((trit_ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + trit_ref.index_in_number));
	trit trit2 = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number));
	return trit1 != trit2;
}

bool operator!=(const TritSet::Reference& ref, const trit& trit_v)
{
	trit t = ref.set->get_trit((ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + ref.index_in_number));
	return t != trit_v;
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
	uint clear_mask = static_cast<uint>(~(0x11 << shift));
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
	trit ref = static_cast<trit>(3 & (trit_ref.set->trits[index_in_number] >> ((BITS_FOR_UINT / BITS_FOR_TRIT - (index_in_number + 1)) * BITS_FOR_TRIT)));
	if (index_in_trit_a >= set->trits.size())
	{
		if (ref == Unknown)
			return (*this);
		else
			reallocate();
	}

	int shift = BITS_FOR_UINT - (index_in_number + 1) * BITS_FOR_TRIT;
	uint clear_mask = static_cast<uint>(~(0x11 << shift));
	set->trits[index_in_trit_a] &= clear_mask;
	uint fill_mask = ref << shift;
	set->trits[index_in_trit_a] |= fill_mask;

	set->last_set_trit_i = index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number;
	if (set->last_set_trit_i > set->last_trit_i)
		set->last_trit_i = set->last_trit_i;
	return (*this);
}

trit TritSet::Reference::operator& (const Reference& trit_ref) const
{
	trit tritrit1 = trit_ref.set->get_trit((trit_ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + trit_ref.index_in_number));
	trit trit2 = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number));
	if (tritrit1 == False || trit2 == False)
		return False;
	if (tritrit1 == True && trit2 == True)
		return True;
	else
		return Unknown;
}

trit TritSet::Reference::operator& (const trit& trit_ref) const
{
	trit t = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number));
	if (t == False || trit_ref == False)
		return False;
	if (t == True && trit_ref == True)
		return True;
	else
		return Unknown;
}

trit operator&(const trit& some_trit, const TritSet::Reference& trit_ref)
{
	trit t = trit_ref.set->get_trit((trit_ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + trit_ref.index_in_number));
	if (t == False || some_trit == False)
		return False;
	if (t == True && some_trit == True)
		return True;
	else
		return Unknown;
}

trit operator&(const trit& trit1, const trit& trit2)
{
	if (trit1 == False || trit2 == False)
		return False;
	if (trit1 == True && trit2 == True)
		return True;
	else
		return Unknown;
}

trit TritSet::Reference::operator| (const Reference& trit_ref) const
{
	trit trit1 = trit_ref.set->get_trit((trit_ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + trit_ref.index_in_number));
	trit trit2 = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number));
	if (trit1 == True || trit2 == True)
		return True;
	if (trit1 == False && trit2 == False)
		return False;
	else
		return Unknown;
}

trit TritSet::Reference::operator| (const trit& trit_ref) const
{
	trit t = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number));
	if (t == False && trit_ref == False)
		return False;
	if (t == True || trit_ref == True)
		return True;
	else
		return Unknown;
}

trit operator|(const trit& some_trit, const TritSet::Reference& trit_ref)
{
	trit t = trit_ref.set->get_trit((trit_ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + trit_ref.index_in_number));
	if (t == False && some_trit == False)
		return False;
	if (t == True || some_trit == True)
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


trit TritSet::Reference::operator~ () const
{
	trit some_trit = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number));
	if (some_trit == True)
		return False;
	if (some_trit == False)
		return True;
	else
		return Unknown;

	set->last_set_trit_i = index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number;
	if (set->last_set_trit_i > set->last_trit_i)
		set->last_trit_i = set->last_trit_i;
}

trit operator~(trit& some_trit)
{
	if (some_trit == True)
		return False;
	if (some_trit == False)
		return True;
	else
		return Unknown;
}

TritSet* TritSet::Reference::get_tritset() const
{
	return set;
}

uint TritSet::Reference::get_arrayindex() const
{
	return index_in_trit_a;
}

uint TritSet::Reference::get_intindex() const
{
	return index_in_number;
}

void TritSet::Reference::set_arrayindex(const uint& new_index) 
{
	index_in_trit_a = new_index;
}

void TritSet::Reference::set_intindex(const uint& new_index)
{
	index_in_number = new_index;
}

std::ostream& operator<<(std::ostream& os, const TritSet::Reference& ref) 
{
	trit t = ref.get_tritset()->get_trit(ref.get_arrayindex() * BITS_FOR_UINT  * BITS_FOR_TRIT / sizeof(uint) +ref.get_intindex());
	if (t == True)
		os << "True";
	else if (t == False)
		os << "False";
	else
		os << "Unknown";
	return os;
}