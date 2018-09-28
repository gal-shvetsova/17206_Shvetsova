#include "TritSet.h"

TritSet::TritSet()
{
	trits.resize(0);
}

TritSet::TritSet(const TritSet& obj)
{
	trits.resize(obj.trits.size());
	last_set_trit_i = obj.last_set_trit_i;
	last_trit_i = obj.last_trit_i;
	for (uint i = 0; i < trits.size(); i++)
		trits[i] = obj.trits[i];
}

TritSet::TritSet(uint new_size)
{
	trits.resize(BITS_FOR_TRIT * new_size / BITS_FOR_UINT);
	last_set_trit_i = -1;
}

trit TritSet::get_trit(const uint& index) const
{
	uint index_in_trit_a = (index * BITS_FOR_TRIT) / (BITS_FOR_UINT);
	uint index_in_number = index % (BITS_FOR_UINT / BITS_FOR_TRIT);
	if (index_in_trit_a >= trits.size())
		return Unknown;
	int shift = BITS_FOR_UINT - BITS_FOR_TRIT*(index_in_number + 1);
	return static_cast<trit> (3 & (trits[index_in_trit_a] >> shift));
}

const TritSet::Reference TritSet::operator[](const int& index) const
{
	size_t array_index = index % (BITS_FOR_UINT / BITS_FOR_TRIT),  //index in number 
		int_index = (index * BITS_FOR_TRIT / BITS_FOR_UINT); // index in array of int
	const Reference ref(this, array_index, int_index);
	return ref;
}

TritSet::Reference TritSet::operator[](const int& index)
{
	size_t array_index = index % (BITS_FOR_UINT / BITS_FOR_TRIT),  //index in number 
		int_index = (index * BITS_FOR_TRIT / BITS_FOR_UINT); // index in array of int
	Reference ref(this, array_index, int_index);
	return ref;
}

TritSet& TritSet::operator=(const TritSet& obj)
{
	int totalsize = BITS_FOR_TRIT * obj.trits.size() / BITS_FOR_UINT ;
	trits.resize(totalsize);
	last_set_trit_i = obj.last_set_trit_i;
	last_trit_i = obj.last_trit_i;
	for (int i = 0; i < totalsize; i++)
		trits[i] = obj.trits[i];
	return *this;
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
	TritSet result(max);
	for (uint i = 0; i < min * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = t_max[i] & t_min[i];
	for (uint i = min * BITS_FOR_UINT / BITS_FOR_TRIT; i < max * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = t_max[i] & Unknown;
	result.last_set_trit_i = min * BITS_FOR_UINT / BITS_FOR_TRIT - 1;
	result.last_trit_i = min * BITS_FOR_UINT / BITS_FOR_TRIT - 1;
	return result;
}

TritSet TritSet::operator|(const TritSet& set) const
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
	TritSet result(max);
	for (uint i = 0; i < min * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = t_max[i] | t_min[i];
	for (uint i = min * BITS_FOR_UINT / BITS_FOR_TRIT; i < max * BITS_FOR_UINT / BITS_FOR_TRIT; i++)
		result[i] = t_max[i] | Unknown;
	result.last_set_trit_i = min * BITS_FOR_UINT / BITS_FOR_TRIT - 1; 
	result.last_trit_i = min * BITS_FOR_UINT / BITS_FOR_TRIT - 1; 
	return result;
}

TritSet::iterator TritSet::begin()
{
	return iterator((*this)[0]);
}

TritSet::iterator TritSet::end()
{
	return iterator((*this)[last_trit_i]);
}

void TritSet::cut_to_trit(uint index)
{
	uint size = index * BITS_FOR_TRIT / BITS_FOR_UINT;
	size += index * BITS_FOR_TRIT % BITS_FOR_UINT;
	for (int i = index; i < last_trit_i; i++)
		trits[i] = Unknown;
	trits.resize(size);
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
	cut_to_trit(last_set_trit_i);
}

void TritSet::trim(uint index)
//forget all from index to the end
{
	for (int i = index; i <= last_trit_i; i++)
		trits[i] = Unknown;
	last_set_trit_i = index;
	last_trit_i = index;
	shrink();
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