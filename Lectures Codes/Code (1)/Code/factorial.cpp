/* File: factorial.cpp
 *
 * A program that computes n!.
 */

#include <iostream>
#include "simpio.h"
using namespace std;

/* Computes n!. */
int factorial(int n);

int main() {
	int num = getInteger("Enter a number: ");
	cout << num << "! = " << factorial(num) << endl;
	return 0;
}

int factorial(int n) {
	if (n == 0) {
		return 1;
	} else {
		return n * factorial(n - 1);
	}
}

