/*******************************************************
 * File: pqueue-linkedlist.h
 *
 * A priority queue class backed by a sorted, singly-linked
 * list.
 */
#ifndef PQueue_LinkedList_Included
#define PQueue_LinkedList_Included

#include <string>
using namespace std;

class LinkedListPriorityQueue {
public:

	/* Constructs a new, empty priority queue backed by a sorted linked list. */
	LinkedListPriorityQueue();

	/* Cleans up all memory allocated by this priority queue. */
	~LinkedListPriorityQueue();

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

	/* A class representing a priority queue backed by a sorted,
	 * singly-linked list.
	 */
	struct node {
		string value;	// Stores value associated with node.
		node* next;		// Stores pointer to next node.
		node(string value, node* next) : value(value), next(next) {}
	};

	node* head; // Stores starting cell of list.
	int elemCount; // Stores count of elements in queue.


	/* Returns pointer of last cell of sorted list wich is less then value*/
	node* lastLessCell(string value);

	/* Puts new node with given value next of index*/
	void putAt(node* &index, string value);

};

#endif
