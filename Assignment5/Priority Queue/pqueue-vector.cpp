/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */

#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {

}

int VectorPriorityQueue::size() {
	return elem.size();
}

bool VectorPriorityQueue::isEmpty() {
	return (size() == 0);
}

void VectorPriorityQueue::enqueue(string value) {
	elem.add(value);
}

string VectorPriorityQueue::peek() {
	if (isEmpty())	error("Queue is Empty!");
	return elem[bestIndex()];
}

string VectorPriorityQueue::dequeueMin() {
	if (isEmpty())	error("Queue is Empty!");

	int ind = bestIndex();
	string answer = elem[ind];
	elem.remove(ind);

	return answer;
}

int VectorPriorityQueue::bestIndex() {
	if (isEmpty()) return -1;
	int answer = 0;

	for (int i = 1; i < elem.size(); i++) {
		if (elem[i] < elem[answer]) {
			answer = i;
		}
	}

	return answer;
}
