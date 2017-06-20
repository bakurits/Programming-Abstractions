#include "OurQueue.h"

bool OurQueue::isEmpty() {
	return in.isEmpty() && out.isEmpty();
}

int OurQueue::size() {
	return in.size() + out.size();
}

void OurQueue::enqueue(int value) {
	in.push(value);
}

int OurQueue::peek() {
	if (out.isEmpty()) {
		while (!in.isEmpty()) {
			out.push(in.pop());
		}
	}
	
	return out.peek();
}

int OurQueue::dequeue() {
	int result = peek();
	out.pop();
	return result;
}
