/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	elemCount = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	node* curNode = head;
	while (curNode != NULL) {
		node* temp = curNode -> next;
		delete (curNode);
		curNode = temp;
		elemCount--;
	}
}


int LinkedListPriorityQueue::size() {
	return elemCount;
}

bool LinkedListPriorityQueue::isEmpty() {
	return (elemCount == 0);
}

LinkedListPriorityQueue::node* LinkedListPriorityQueue::lastLessCell(string value) {
	if (isEmpty()) return NULL;

	node* curNode = head;

	if (curNode->value >= value) return NULL;

	while (true) {
		if (curNode->next == NULL || curNode->next->value >= value) {
			return curNode;
		} else {
			curNode = curNode->next;
		}
	}

}

void LinkedListPriorityQueue::putAt(LinkedListPriorityQueue::node* &index, string value) {
	if (index != NULL) {
		if (index->next != NULL) {
			node *temp = index->next;
			index->next = new node(value, temp);
		} else {
			index->next = new node(value, NULL);
		}
	} else {
		node* temp = new node(value, head);
		head = temp;
	}
}

void LinkedListPriorityQueue::enqueue(string value) {
	node* curNode = new node(value, NULL);

	if (isEmpty()) {
		head = curNode;
		elemCount++;
		return;
	}
	elemCount++;
	node* placeOfNewElement = lastLessCell(value);
	putAt(placeOfNewElement, value);
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty())	error("queue is empty");
	return head -> value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (isEmpty())	error("queue is empty");

	string answer = peek();

	node* temp = head;
	head = head -> next;
	delete(temp);

	elemCount--;

	return answer;

}
