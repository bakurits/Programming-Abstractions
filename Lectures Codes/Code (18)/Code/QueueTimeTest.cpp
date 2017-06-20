/*****************************************************
 * File: QueueTimeTest.cpp
 *
 * A program to run stress tests of our queue.
 */
#include <iostream>
#include <ctime>
#include "OurQueue.h"
#include "queue.h"
#include "simpio.h"
#include "random.h"
using namespace std;

const int kMaximumSize   = 1000000;
const int kNumIterations = 100;

template <typename QueueType>
	void runTimeTrial(string type) {

	double startTime = clock();

	QueueType Queue;
	
	for (int iteration = 0; iteration < kNumIterations; iteration++) {
	
		/* Enqueue, then dequeue, a huge number of elements. */
		for (int elem = 0; elem < kMaximumSize; elem++) {
			Queue.enqueue(elem);
		}
		for (int elem = 0; elem < kMaximumSize; elem++) {
			Queue.dequeue();
		}
	
	}
		
	double elapsed = (clock() - startTime) / double(CLOCKS_PER_SEC);
	cout << "Enq/Deq " << kMaximumSize
	     << " ints " << kNumIterations << " times using a "
	     << type << ": " << elapsed << "s" << endl;
}

int main() {
	runTimeTrial< OurQueue > ("linked list");
	runTimeTrial< Queue<int> >("dynamic array");
	
	return 0;
}
