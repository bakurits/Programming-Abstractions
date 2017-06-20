/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */
#include <iostream>
#include "pqueue-extra.h"
#include "simpio.h"
#include "error.h"

/**/
const int defSize = 4;

ExtraPriorityQueue::ExtraPriorityQueue() {
	minRoot = NULL;
	rootCount = 0;
	elemCount = 0;
	allocatedLength = defSize;
	degreeFreq = new node*[defSize];
	for (int i = 0; i < defSize; i++) {
		degreeFreq[i] = NULL;
	}
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
	clearMemory(minRoot);
}

int ExtraPriorityQueue::size() {
	return elemCount;
}

bool ExtraPriorityQueue::isEmpty() {
	return (size() == 0);
}

void ExtraPriorityQueue::deleteRoot(node* &curNode) {
	if (degreeFreq[curNode->childCount] == curNode) {
		degreeFreq[curNode->childCount] = NULL;
	}
	rootCount--;
	delete curNode;
}

void ExtraPriorityQueue::balanceHeap() {
	if (isEmpty()){
		rootCount = 0;
		return;
	}

	node* curNode = minRoot;
	node* newMin = minRoot;

	int n = rootCount;

	for (int i = 0; i < n; i++){
		if (curNode->value < newMin->value) newMin = curNode;
		node* temp = curNode->right;
		int curDegree = curNode->childCount;

		if (curDegree >= allocatedLength) grow();

		if (degreeFreq[curDegree] != NULL && degreeFreq[curDegree] != curNode) {
			mergeRoots(curNode, degreeFreq[curDegree]);
			rootCount--;
		} else {
			degreeFreq[curDegree] = curNode;
		}
		curNode = temp;
	}
	
	n = rootCount;
	for (int i = 0; i < n; i++) {
		if (curNode->value < newMin->value) newMin = curNode;
		curNode = curNode->right;
	}
	minRoot = newMin;
}

void ExtraPriorityQueue::removeMinNode() {
	rootCount += minRoot->childCount;
	if (minRoot->left == minRoot) {
		node* temp = minRoot;
		rootCount = minRoot->childCount + 1;
		minRoot = minRoot->child;
		deleteRoot(temp);
		return;
	}

	node* leftNode = minRoot->left;
	node* rightNode = minRoot->right;
	node* midNode = minRoot->child;
	deleteRoot(minRoot);

	if (midNode != NULL) {
		leftNode->right = midNode;
		rightNode->left = midNode->left;
		midNode->left->right = rightNode;
		midNode->left = leftNode;
	} else {
		leftNode->right = rightNode;
		rightNode->left = leftNode;
	}

	minRoot = leftNode;
}

void ExtraPriorityQueue::clearMemory(node* curNode) {
	if (curNode == NULL) return;
	clearMemory(curNode->child);

	node* startNode = curNode;
	do {
		node* nextNode = curNode->right;
		delete curNode;
		curNode = nextNode;
	} while (curNode != startNode);
}

void ExtraPriorityQueue::enqueue(string value) {
	node* newNode = new node(value);
	if (isEmpty()) {
		newNode->left = newNode->right = newNode;
		minRoot = newNode;
	} else {
		insertAfter(minRoot, newNode);
		if (newNode->value < minRoot->value)
			minRoot = newNode;
	}
	elemCount++;
	rootCount++;
}

string ExtraPriorityQueue::peek() {
	if (isEmpty()) error("Queue is empty!");
	return minRoot->value;
}

string ExtraPriorityQueue::dequeueMin() {
	string answer = peek();
	balanceHeap();
	removeMinNode();
	elemCount--;
	return answer;
}

void ExtraPriorityQueue::mergeRoots(node* first, node* second) {
	if (first->value > second->value)
		swap(first, second);
	second->left->right = second->right;
	second->right->left = second->left;
	if (first->childCount) {
		insertAfter(first->child, second);
		first->childCount++;
	} else {
		first->child = second;
		first->childCount = 1;
		second->left = second->right = second;
	}
	int curDegree = first->childCount;

	if (curDegree >= allocatedLength) grow();
	degreeFreq[curDegree - 1] = NULL;

	if (degreeFreq[curDegree] != NULL) {
			mergeRoots(first, degreeFreq[curDegree]);
			rootCount--;
	} else {
		degreeFreq[curDegree] = first;
	}

}

void ExtraPriorityQueue::grow() {
	allocatedLength *= 2;
	node** tmp = new node*[allocatedLength];
	for (int i = 0; i < allocatedLength; i++) {
		if (i < allocatedLength/2) {
			tmp[i] = degreeFreq[i];
		} else {
			tmp[i] = NULL;
		}
	}
	delete [] degreeFreq;
	degreeFreq = tmp;
}

void ExtraPriorityQueue::insertAfter(node* &curNode, node* &newNode) {
	newNode->right = curNode->right;
	newNode->left = curNode;
	curNode->right->left = newNode;
	curNode->right = newNode;
}
