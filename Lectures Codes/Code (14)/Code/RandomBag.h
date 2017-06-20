/******************************************************
 * File: RandomBag.h
 *
 * A class representing a bag of elements in which
 * values can be added and then removed randomly.
 */
#ifndef RandomBag_Included
#define RandomBag_Included

#include "vector.h"

class RandomBag {
public:
	int  size();
	bool isEmpty();
	void add(int toAdd);
	int removeRandom();
	
private:
	Vector<int> elems;
}; // <--- note there's a semicolon here!!!

#endif
