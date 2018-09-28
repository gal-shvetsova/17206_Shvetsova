#include "TritSet.h"
#include "Other.h"
#include <iostream>

TritSet::Trit_Iterator::Trit_Iterator(const TritSet::Trit_Iterator& iter) : pointer(iter.pointer){}

TritSet::Trit_Iterator::Trit_Iterator(const TritSet::Reference t_ref) : pointer(t_ref){}

bool TritSet::Trit_Iterator::operator!=(TritSet::Trit_Iterator const& other) const
{
	if (pointer.get_tritset() == other.pointer.get_tritset() && pointer.get_arrayindex() == other.pointer.get_arrayindex() && pointer.get_intindex() == other.pointer.get_intindex())
		return 0;
	return 1;
}
bool TritSet::Trit_Iterator::operator==(Trit_Iterator const& other) const
{
	if (pointer.get_tritset() == other.pointer.get_tritset() && pointer.get_arrayindex() == other.pointer.get_arrayindex() && pointer.get_intindex() == other.pointer.get_intindex())
		return 1;
	return 0;
}

trit TritSet::Trit_Iterator::operator*() const
{
	return pointer.get_tritset()->get_trit(pointer.get_arrayindex() * BITS_FOR_UINT * BITS_FOR_TRIT / sizeof(uint) + pointer.get_intindex());
}

TritSet::Trit_Iterator& TritSet::Trit_Iterator::operator++()
{
	pointer.set_intindex(pointer.get_intindex() + 1);
	if (pointer.get_intindex() == (BITS_FOR_UINT / BITS_FOR_TRIT)){
		pointer.set_intindex(0);
		pointer.set_arrayindex(pointer.get_arrayindex() + 1);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const TritSet::iterator ref)
{
	os << ref.pointer;
	return os;
}
