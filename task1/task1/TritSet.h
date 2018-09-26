#ifndef TRITSET_H
#define TRITSET_H

#include <vector>
#include "stdint.h"
#include "Trit.h"
#include "Other.h"



class TritSet
{
public:

	class Reference { 
	protected:
		TritSet *set;  // pointer to number from array
		size_t index_in_number; // index in number
		size_t index_in_trit_a; //index in array
		void reallocate(); 
	public:
		Reference(const TritSet*, size_t, size_t);
		Reference(TritSet*, size_t, size_t);

		bool operator==(const Reference&);
		bool operator==(const trit&);

		Reference operator= (const trit&); // t[i] = x
		Reference operator= (const Reference&); // t[i] = t[j]

		trit operator& (const Reference&) const;
		trit operator| (const Reference&) const;
		trit operator~ () const;
		//~Reference();
	};

	TritSet();
	TritSet(const TritSet&);  //copy ??
	explicit TritSet(uint);  //create vector with some size 

	trit get_trit(uint) const;

	TritSet& operator=(const TritSet&);
	Reference operator[](const int&) const;

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

//	~TritSet();
private:
	std::vector<uint> trits;
	size_t totalsize;

};

#endif