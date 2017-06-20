#include "OurQueue.h"
#include "error.h"

OurQueue::OurQueue() {
	head = tail = NULL;
	logLen = 0;
}

OurQueue::~OurQueue() {
	while (head != NULL) {
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

int OurQueue::size() {
	return logLen;
}

bool OurQueue::isEmpty() {
	return head == NULL;
}

void OurQueue::enqueue(int value) {
	Cell* cell = new Cell;
	cell->value = value;
	cell->next = NULL;
	
	if (head == NULL) {
		head = tail = cell;
	} else {
		tail->next = cell;
		tail = cell;
	}
}

int OurQueue::front() {
	if (isEmpty()) {
		error("And lo!  The queue was empty.");
	}
	return head->value;
}

int OurQueue::dequeue() {
	int result = front();
	
	Cell* next = head->next;
	delete head;
	head = next;
	
	if (head == NULL) tail = NULL;
	
	return result;
}


