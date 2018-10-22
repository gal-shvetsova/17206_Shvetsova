#include "TritSet.h"

TritSet::TritSet()
{
	trits.resize(0);
}

TritSet::TritSet(uint new_size)
{
	trits.resize(BITS_FOR_TRIT * new_size / BITS_FOR_UINT + 1);
}

const trit TritSet::operator[](const int& index) const
{
	size_t array_index = index % (BITS_FOR_UINT / BITS_FOR_TRIT),  //index in number 
		int_index = (index * BITS_FOR_TRIT / BITS_FOR_UINT); // index in array of int
	Reference ref(this, array_index, int_index);
	return ref.get_trit();
}

TritSet::Reference TritSet::operator[](const int& index)
{
	size_t array_index = index % (BITS_FOR_UINT / BITS_FOR_TRIT),  //index in number 
		int_index = (index * BITS_FOR_TRIT / BITS_FOR_UINT); // index in array of int
	Reference ref(this, array_index, int_index);
	return ref;
}

TritSet TritSet::operator&(const TritSet& set)  const
{
	int max, min;
	TritSet t_max, t_min;
	if (trits.size() > set.trits.size())
	{
		max = trits.size();
		min = set.trits.size();
		t_max = (*this);
		t_min = set;
	}
	else
	{
		max = set.trits.size();
		min = trits.size();
		t_min = (*this);
		t_max = set;
	}
	TritSet result;
	result.trits.resize(max - 1);
	for (uint i = 0; i < (min) * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = t_max[i] & t_min[i];
	for (uint i = (min)  * BITS_FOR_UINT / BITS_FOR_TRIT; i < (max + 1) * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = t_max[i] & Unknown;
	result.last_set_trit_i = (min)* BITS_FOR_UINT / BITS_FOR_TRIT - 1;
	result.last_trit_i = (min) * BITS_FOR_UINT / BITS_FOR_TRIT - 1;
	return result;
}

TritSet TritSet::operator|(const TritSet& set) const
{
	int max, min ;
	TritSet t_max, t_min;
	if (trits.size() > set.trits.size())
	{
		max = trits.size();
		min = set.trits.size();
		t_max = (*this);
		t_min = set;
	}
	else
	{
		max = set.trits.size();
		min = trits.size();
		t_min = (*this);
		t_max = set;
	}
	TritSet result;
	result.trits.resize(max - 1);
	for (uint i = 0; i < min * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = t_max[i] | t_min[i];
	for (uint i = min * BITS_FOR_UINT / BITS_FOR_TRIT; i < max * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = t_max[i] | Unknown;
	result.last_set_trit_i = min * BITS_FOR_UINT / BITS_FOR_TRIT - 1; 
	result.last_trit_i = min * BITS_FOR_UINT / BITS_FOR_TRIT - 1; 
	return result;
}

TritSet TritSet::operator~() const
{
	TritSet result(last_trit_i);
	for (uint i = 0; i <= last_trit_i * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = ~(*this)[i];
	result.last_set_trit_i = last_trit_i * BITS_FOR_UINT / BITS_FOR_TRIT;
	result.last_trit_i = last_trit_i * BITS_FOR_UINT / BITS_FOR_TRIT;
	return result;
}

void TritSet::shrink()
//forget all from last set trit to the end
{
	if (last_set_trit_i < 0)
	{
		trits.resize(0);
		last_set_trit_i = -1;
		return;
	}
	trim(last_set_trit_i);
}

void TritSet::trim(uint index)
//forget all from index to the end
{
	uint size = index / (BITS_FOR_UINT / BITS_FOR_TRIT);
	size += index % (BITS_FOR_UINT / BITS_FOR_TRIT) ? 1 : 0;
	for (int i = index; i <= last_trit_i; i++)
		(*this)[i] = Unknown;
	last_set_trit_i = index;
	last_trit_i = index;
	trits.resize(size);
}

uint TritSet::length()
//logical lenght
{
	for (int i = last_trit_i; i >= 0; i--)
	{
		if ((*this)[i] != Unknown)
			return i;
	}
	return last_trit_i;
}

uint TritSet::cardinality(trit value) const
//count trit in some state
{
	int count = 0;
	for (int i = 0; i <= last_trit_i; i++)
	{
		if ((*this)[i] == value) 
			count++;
	}
	return count;
}

std::unordered_map<trit, uint> TritSet::cardinality()
//count trits in every state
{
	std::unordered_map<trit, uint> result;
	result[True] = cardinality(True);
	result[False] = cardinality(False);
	result[Unknown] = cardinality(Unknown);
	return result;
}