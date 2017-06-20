/*******************************************************
 * File: pqueue-doublylinkedlist.h
 *
 * A priority queue class backed by an unsorted, doubly-linked
 * list.
 */
#ifndef PQueue_DoublyLinkedList_Included
#define PQueue_DoublyLinkedList_Included

#include <string>
using namespace std;

/* A class representing a priority queue backed by an unsorted,
 * doubly-linked list.
 */
class DoublyLinkedListPriorityQueue {
public:

	/* Constructs a new, empty priority queue backed by a doubly-linked list. */
	DoublyLinkedListPriorityQueue();

	/* Cleans up all memory allocated by this priority queue. */
	~DoublyLinkedListPriorityQueue();

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

	// Stores value and pointers on next and previous element
	struct node {
		string value;	// Stores value associated with node.
		node* prev;		// Stores pointer to previous node.
		node* next;		// Stores pointer to next node.
		node(string value, node* prev, node* next) : value(value), prev(prev), next(next) {}
	};

	int elemCount; // Counts number of elements in queue.
	node* head; // Stores first element in queue.


	/* This method returns pointer of minimum value in queue. */
	node* getBestIndex();

	/* This method merges two cells of queue.
	 * Makes them adjacent.
	 */
	void mergePrt(node* &first, node* &second);

};

#endif
