/**********************************************
 * File: pqueue-extra.h
 *
 * Your own custom priority queue class, if you
 * want to build one for extra credit.
 *
 * Please replace these file comments with a
 * description of how your priority queue works.
 */
#ifndef PQueue_Extra_Included
#define PQueue_Extra_Included

#include <string>
#include <vector>
using namespace std;

class ExtraPriorityQueue {
public:
	/* Constructs a new, empty priority queue. */
	ExtraPriorityQueue();

	/* Cleans up all memory allocated by this priority queue. */
	~ExtraPriorityQueue();

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
	struct node{
		string value; 	// Stores value of node
		node* child; 	// Stores pointer to one of child node. Leaf nodes have Null pointer there.
		node* left;		// Stores pointer to the left node.
		node* right;	// Stores pointer to the right node.
		int childCount;	// Stores count of children for current node.

		node(string value) : value(value), child(NULL), left(NULL), right(NULL), childCount(0) {}
	};

	int allocatedLength; // Stores size of allocated memory

	int elemCount; // Stores count of elements in queue.
	node* minRoot; // Stores pointer to the root with minimum value.
	int rootCount; // Stores number of roots.

	node** degreeFreq; // Stores pointer to the node in index related with node's childCount.

	/**/
	void grow();

	/* This method removes root from rootlist and adds it's children there. */
	void removeMinNode();

	/* This method balances heap after deleting node. */
	void balanceHeap();

	/* This method clears allocated memory */
	void clearMemory(node* curNode);

	/* This method deletes node from memory*/
	void deleteRoot(node* &curNode);

	/* This methode merges two root. */
	void mergeRoots(node* first, node* second);

	/* This method inserts node after current node in list. */
	void insertAfter(node* &curNode, node* &newNode);
};

//#include "pqueue-extra.cpp"

#endif
