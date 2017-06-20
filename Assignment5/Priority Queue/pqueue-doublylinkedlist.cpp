/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */

#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	elemCount = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	node* curNode = head;
	while (curNode != NULL) {
		node* temp = curNode -> next;
		delete(curNode);
		curNode = temp;
		elemCount--;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return elemCount;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return (elemCount == 0);
}

void DoublyLinkedListPriorityQueue::mergePrt(node* &first, node* &second) {
	if (first != NULL) {
		first->next = second;
		if (second != NULL)
			second->prev = first;
	} else {
		if (second != NULL)
			second->prev = first;
		head = second;
	}
}

DoublyLinkedListPriorityQueue::node* DoublyLinkedListPriorityQueue::getBestIndex() {
 	if (isEmpty()) return NULL;
 	node* curNode = head;
 	node* answer = head;

 	while (curNode != NULL) {
 		if (curNode->value < answer->value) answer = curNode;
 		curNode = curNode->next;
 	}

 	return answer;
 }

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	node* newNode = new node(value, NULL, head);

	if (head != NULL)
		head->prev = newNode;
	head = newNode;
	elemCount++;

}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty())	error("Queue is empty");

	node* bestIndex = getBestIndex();
	return bestIndex->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty())	error("Queue is empty");

	string answer = peek();
	node* bestIndex = getBestIndex();

	mergePrt(bestIndex->prev, bestIndex->next);
	delete(bestIndex);
	elemCount--;

	return answer;
}
