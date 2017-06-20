/**********************************************
 * File: pqueue-heap.h
 *
 * A priority queue class backed by a binary
 * heap.
 */
#ifndef PQueue_Heap_Included
#define PQueue_Heap_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by an
 * binary heap.
 */
class HeapPriorityQueue {
public:
	/* Constructs a new, empty priority queue backed by a binary heap. */
	HeapPriorityQueue();

	/* Cleans up all memory allocated by this priority queue. */
	~HeapPriorityQueue();

	/* Returns the number of elements in the priority queue. */
	int size();

	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();

	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);

	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();

	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();

private:
	int  allocatedLength; // Indicates how much space is allocated in our array.
	int  logicalLength;   // Indicates how many elements are logically in the array.
	string* elems;        // Stores actual array of elements.

	/* This method controls grow and decay of dinamic array.
	 * If indicator is 1 array grows
	 * If it's -1 than it decays.
	 */
	void changeSizeOfArray(int indicator);

	/* This method balances new tree from bottom to top. */

	void balanceFromBottom(int index);


	/* This method balances new tree from top to bottom. */
	void balanceFromTop(int index);


	/* If index have only one child it's also one with minimum value.
	/* This method finds childs index which have less value.
	 */
	int getMinChild(int index);

};

#endif
