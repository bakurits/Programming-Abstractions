#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
using namespace std;
void VectorTest(int numToAdd);
void QueueTest(int numToAdd);

int main() {
	int numToAdd = 100000;
	
	cout << "Starting..." << endl;

	time_t beginTime = time(NULL);
	VectorTest(numToAdd);
	time_t endTime = time(NULL);
	cout << "Vector Time: " << endTime-beginTime << " seconds" << endl;

	beginTime = time(NULL);
	QueueTest(numToAdd);
	endTime = time(NULL);
	cout << "Queue Time: " << endTime-beginTime << " seconds" << endl;

	return 0;
}

void VectorTest(int numToAdd) {
	Vector<int> v;
	for (int i = 0; i < numToAdd; i++) {
		v += i;
	}
	for (int i = 0; i < numToAdd; i++) {
		v.remove(0);
	}
}

void QueueTest(int numToAdd) {
	Queue<int> q;
	for (int i = 0; i < numToAdd; i++) {
		q.enqueue(i);
	}
	for (int i = 0; i < numToAdd; i++) {
		q.dequeue();
	}
}

