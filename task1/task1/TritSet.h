#ifndef TRITSET_H
#define TRITSET_H

#include <vector>
#include "stdint.h"
#include "Other.h"
#include <unordered_map>


class TritSet
{
public:

	class Reference { 
	private:
		TritSet *set;  // pointer to number from array
		uint index_in_number; // index in number
		uint index_in_trit_a; //index in array
		void reallocate(); 
	public:
		Reference(const TritSet*, uint, uint); 
		Reference(TritSet*, uint, uint); 

		friend bool operator==(const Reference&, const trit&);
		bool operator==(const Reference&) const;
		bool operator!=(const Reference) const;
		friend bool operator!=(const Reference&, const trit&);

		Reference operator= (const trit&); // t[i] = x
		Reference operator= (const Reference&); // t[i] = t[j] 

		trit operator& (const trit&) const;
		trit operator& (const Reference&) const;
		friend trit operator&(const trit&, const trit&);
		friend trit operator&(const trit&, const TritSet::Reference&);

		trit operator| (const trit&) const;
		trit operator| (const Reference&) const;
		friend trit operator|(const trit&, const trit&);
		friend trit operator|(const trit&, const TritSet::Reference&);
		
		trit operator~ () const;
		friend trit operator~(const trit&);

		
		TritSet* get_tritset() const;
		uint get_intindex() const;
		uint get_arrayindex() const;
		void set_intindex(const uint&);
		void set_arrayindex(const uint&);

		friend std::ostream& operator<<(std::ostream& os, const Reference&);
	};

	TritSet();
	explicit TritSet(uint);  //create vector with some size 

	trit get_trit(const uint&) const;
	const int get_size() const;
	const int get_last_set_i() const;
	const int get_last_i() const;

	TritSet& operator=(const TritSet&); //удалить
	
	const Reference operator[](const int&) const;
	Reference operator[](const int& index);

	TritSet operator&(const TritSet&) const;
	TritSet operator|(const TritSet&) const;
	TritSet operator~() const;

	void cut_to_trit(uint);
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
