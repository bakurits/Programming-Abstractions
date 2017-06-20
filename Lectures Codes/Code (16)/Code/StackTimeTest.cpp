/*****************************************************
 * File: StackTimeTest.cpp
 *
 * A program to run stress tests of our stack.
 */
#include <iostream>
#include <ctime>
#include "OurStack.h"
#include "simpio.h"
#include "random.h"
using namespace std;

const int kMinimumSize = 1000000;
const int kMaximumSize = 10000000;
const int kStepSize = 1000000;

int main() {
	for (int i = kMinimumSize; i <= kMaximumSize; i += kStepSize) {
		double startTime = clock();
	
		OurStack stack;
		for (int elem = 0; elem < i; elem++) {
			stack.push(elem);
		}
		
		for (int elem = 0; elem < i; elem++) {
			stack.pop();
		}
		
		double elapsed = (clock() - startTime) / double(CLOCKS_PER_SEC);
		cout << "Time for " << i << ": " << elapsed << "s" << endl;
	}
	
	return 0;
}
