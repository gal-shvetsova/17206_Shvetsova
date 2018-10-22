#ifndef TRITSET_H
#define TRITSET_H

#include <vector>
#include "stdint.h"
#include "Trit.h"
#include <unordered_map>


typedef unsigned int uint;
const uint BITS_FOR_TRIT = 2;
const uint BITS_FOR_UINT = sizeof(uint) * 8;

class TritSet
{
public:
	
	class Reference { 
		friend TritSet;
	private:
		TritSet *set;  // pointer to number from array
		uint index_in_number; // index in number
		uint index_in_trit_a; //index in array
		Reference(const TritSet*, uint, uint);
		Reference(TritSet*, uint, uint);
		void reallocate(); 
	public:
		Reference operator= (const trit&); // t[i] = x
		Reference operator= (const Reference&); // t[i] = t[j] 

		operator trit() const;
		
		trit get_trit() const;

		friend std::ostream& operator<<(std::ostream& os, const Reference&);
	};

	TritSet();
	explicit TritSet(uint);  //create vector with some size 

	const trit operator[](const int&) const;
	Reference operator[](const int&);

	TritSet operator&(const TritSet&) const;
	TritSet operator|(const TritSet&) const;
	TritSet operator~() const;

	void shrink();
	std::unordered_map< trit, uint > cardinality();
	void trim(uint); // forget contain of trits starting from lastIndex
	uint length(); // index of last non-uknown trit +1
	uint cardinality(trit value) const; // count of trits in some state
private:
	std::vector<uint> trits;
	int last_trit_i = -1;
	int last_set_trit_i = -1;
};

#endif
