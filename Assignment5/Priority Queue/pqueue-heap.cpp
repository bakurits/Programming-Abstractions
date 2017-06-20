/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */

#include "pqueue-heap.h"
#include "error.h"

/* Constant controlling the default size of our queue. */
const int kDefaultSize = 8;

/* Constant controlling grow and decay of dinamic array. */
const int kDefaultChangingValue = 2;

HeapPriorityQueue::HeapPriorityQueue() {
	logicalLength = 1;
	allocatedLength = kDefaultSize;
	elems = new string[allocatedLength];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] elems;
	logicalLength = allocatedLength = 0;
}

int HeapPriorityQueue::size() {
	return logicalLength - 1;
}

bool HeapPriorityQueue::isEmpty() {
	return (size() == 0);
}

void HeapPriorityQueue::enqueue(string value) {
	if (logicalLength == allocatedLength) {
		changeSizeOfArray(1);
	}
	elems[logicalLength++] = value;
	balanceFromBottom(logicalLength - 1);
}

string HeapPriorityQueue::peek() {
	if (isEmpty()) error("queue is empty");
	return elems[1];
}

string HeapPriorityQueue::dequeueMin() {
	if (isEmpty()) error("queue is empty");
	string answer = peek();

	swap(elems[1], elems[--logicalLength]);
	balanceFromTop(1);

	if (logicalLength * kDefaultChangingValue * kDefaultChangingValue < allocatedLength && allocatedLength > kDefaultSize) {
		changeSizeOfArray(-1);
	}

	return answer;
}

void HeapPriorityQueue::changeSizeOfArray(int indicator) {
	if (indicator > 0) {
		allocatedLength *= kDefaultChangingValue;
	} else {
		allocatedLength /= kDefaultChangingValue;
	}

	string* newArray = new string[allocatedLength];

	for (int i = 0 ; i < logicalLength; i++) {
		newArray[i] = elems[i];
	}

	delete[] (elems);
	elems = newArray;

}

int HeapPriorityQueue::getMinChild(int index) {
	int leftChild = index << 1;
	int rightChild = index << 1 | 1;

	if (rightChild >= logicalLength) return leftChild;

	return elems[leftChild] <= elems[rightChild] ? leftChild : rightChild;
}

void HeapPriorityQueue::balanceFromBottom(int index) {
	while (index > 1) {
		if (elems[index] < elems[index >> 1]) {
			swap(elems[index], elems[index >> 1]);
			index = index >> 1;
		} else {
			break;
		}
	}
}

void HeapPriorityQueue::balanceFromTop(int index) {
	while (true) {
		int minChild = getMinChild(index);
		if (minChild >= logicalLength) break;

		if (elems[minChild] < elems[index]) {
			swap(elems[minChild], elems[index]);
			index = minChild;
		} else {
			break;
		}
	}
}
