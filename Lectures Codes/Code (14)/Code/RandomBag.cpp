#include "RandomBag.h"
#include "random.h"

int RandomBag::size() {
	return elems.size();
}

void RandomBag::add(int toAdd) {
	elems += toAdd;
}

bool RandomBag::isEmpty() {
	return size() == 0;
}

int RandomBag::removeRandom() {
	if (isEmpty()) {
		error("You cannot form somethingness from nothingness.");
	}

	int index = randomInteger(0, size() - 1);
	int result = elems[index];
	elems.remove(index);
	
	return result;
}




