/*****************************************************
 * File: StackSimpleTest.cpp
 *
 * A program to run simple tests on our custom Stack.
 */
#include <iostream>
#include "OurQueue.h"
#include "simpio.h"
#include "random.h"
using namespace std;

const int kNumElems = 4;

int main() {
	OurQueue queue;
	
	/* Load the stack with random values. */
	for (int i = 0; i < kNumElems; i++) {
		int value = randomInteger(0, 1000);
		cout << "Enqueuing " << value << " into the queue." << endl;
		queue.enqueue(value);
	}
	
	/* See what those values are. */
	while (!queue.isEmpty()) {
		cout << "Dequeued " << queue.dequeue() << " from the queue." << endl;
	}
	
	return 0;
}
