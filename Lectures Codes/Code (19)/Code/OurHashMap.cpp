#include "OurHashMap.h"
#include "error.h"
using namespace std;

/* * * * * Helper Functions * * * * */

/* 
 * Function hashCode
 * Usage: int code = hashCode(key)
 * ---------------------------------------------------------
 * An hash function for strings. Adapted from code online at
 * http://www.daniweb.com/software-development/cpp/threads/231987/string-hash-function
 * This function is called a SAX hash function (Shift-Add-XOR) and is
 * great at distributing strings evenly.
 */
const int kHashMask = 0x7FFFFFFF;
int hashCode(string key) {
    int hashVal = 0;
    for (int x = 0; x < key.length(); ++x) {
        hashVal ^= (hashVal << 5) +
                   (hashVal >> 2) +
                   key[x];
    }
    return hashVal & kHashMask;
}

/* * * * * Implementation of OurHashMap. * * * * */

const int kNumBuckets = 7;

OurHashMap::OurHashMap() {
	numBuckets = kNumBuckets;
	numElems = 0;
	buckets = new Cell*[numBuckets];
	for (int i = 0; i < kNumBuckets; i++)
		buckets[i] = NULL;
}

OurHashMap::~OurHashMap() {
	for (int i = 0; i < numBuckets; i++) {
		Cell *head = buckets[i];
		while (head != NULL) {
			Cell *next = head->next;
			delete head;
			head = next;
		}
	}
	delete[] buckets;
}


OurHashMap::Cell * OurHashMap::findCell(string key) {
	int index = hashCode(key) % numBuckets;
	Cell *head = buckets[index];
	while (head != NULL) {
		if (head->key == key)
			return head;
		head = head->next;
	}
	return NULL;
}

int OurHashMap::get(string key) {
	Cell *cell = findCell(key);
	if (cell == NULL)
		error("Key is not in map");
	return cell->value;
}

bool OurHashMap::containsKey(string key) {
	Cell *cell = findCell(key);
	return cell != NULL;
}

void OurHashMap::put(string key, int value) {	
	Cell *cell = findCell(key);
	if (cell != NULL) {
		cell->value = value;
	} else {
		int index = hashCode(key) % numBuckets;
		Cell *newCell = new Cell;
		newCell->key = key;
		newCell->value = value;
		newCell->next = buckets[index];
		buckets[index] = newCell;
		numElems++;
	}
}

int OurHashMap::size() {
	return numElems;
}

bool OurHashMap::isEmpty() {
	return size() == 0;
}


void OurHashMap::increaseBuckets() {
	int newBucketsNum = numBuckets * 2;
	Cell ** newBuckets = new Cell*[tmp];
	for (int i = 0; i < newBucketsNum; i++)
		newBuckets[i] = NULL;


	for (int i=0; i<numBuckets; i++) {		
		Cell *head = buckets[i];
		while (head != NULL) {
			int index = hashCode(head->key) % newBucketsNum;
			Cell * tmpCell = head->next;
			head->next = newBuckets[index];
			newBuckets[index] = head; 

			head = tmpCell;
		}
		
	}

		
	
}