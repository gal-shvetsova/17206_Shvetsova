#include "TritSet.h"

TritSet::Reference::Reference(const TritSet* other, size_t i, size_t a)
{
	set = const_cast<TritSet*>(other);
	index_in_number = i;
	index_in_trit_a = a;
}

TritSet::Reference::Reference(TritSet* other, size_t i, size_t a)
{
	set = other;
	index_in_number = i;
	index_in_trit_a = a;
}

void TritSet::Reference::reallocate()
//reallocate memory for trits array
{
	size_t new_size = (int)(index_in_trit_a * BITS_FOR_TRIT / BITS_FOR_UINT);
	set->totalsize = new_size;
	set->trits.resize(new_size);
}

trit TritSet::get_trit(uint index) const
{
	uint index_in_trit_a = (index * BITS_FOR_TRIT) / (BITS_FOR_UINT);
	uint index_in_number = index % (BITS_FOR_UINT / BITS_FOR_TRIT);
	if (index_in_trit_a >= totalsize / BITS_FOR_TRIT) return Unknown;
	int shift = (BITS_FOR_UINT / BITS_FOR_TRIT - (index_in_number + 1)) * BITS_FOR_TRIT;
	return  static_cast<trit>(2 & (trits[index_in_trit_a] >> shift));
}

bool TritSet::Reference::operator==(const Reference& trit_ref)
{
	trit t1 = trit_ref.set->get_trit((trit_ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint) * BITS_FOR_TRIT + trit_ref.index_in_number));
	trit t2 = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint) * BITS_FOR_TRIT + index_in_number));
	return t1 == t2;
}

bool TritSet::Reference::operator==(const trit& trit_v)
{
	trit t = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number));
	return t == trit_v;
}

TritSet::Reference TritSet::Reference::operator= (const trit& trit_ref)
{

	if (index_in_trit_a >= set->totalsize)
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
	return (*this);
}

TritSet::Reference TritSet::Reference::operator= (const Reference& trit_ref)
{
	//if (trit_ref == *(this))
	//	return trit_ref;
	trit ref = static_cast<trit>(3 & (trit_ref.set->trits[index_in_number] >> ((BITS_FOR_UINT / BITS_FOR_TRIT - (index_in_number + 1)) * BITS_FOR_TRIT)));
	if (index_in_trit_a >= set->totalsize)
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
	return (*this);
}

trit TritSet::Reference::operator& (const Reference& trit_ref) const
{
	trit t1 = trit_ref.set->get_trit((trit_ref.index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + trit_ref.index_in_number));
	trit t2 = set->get_trit((index_in_trit_a * BITS_FOR_UINT / sizeof(uint)* BITS_FOR_TRIT + index_in_number));
	if (t1 == False || t2 == False)
		return False;
	if (t1 == True && t2 == True)
		return True;
	else
		return Unknown;
}

//TritSet::Reference::~Reference()
//{
//	delete set;
//}