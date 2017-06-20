/* File: digital-roots.cpp
 *
 * A program to compute digital roots.
 */
#include <iostream>
#include "simpio.h"
using namespace std;

int digitalRoot(int num);
int sumOfDigits(int n);

int main() {
	while (true) {
		int value = getInteger("Enter an integer: ");
		cout << value << " has digital root " << digitalRoot(value) << endl;
	}
}

int digitalRoot(int n) {
	if (n < 10) {
		return n;
	} else {
		return digitalRoot(sumOfDigits(n));
	}
}

int sumOfDigits(int n) {
	if (n < 10) {
		return n;
	} else {
		return (n % 10) + sumOfDigits(n / 10);
	}
}











