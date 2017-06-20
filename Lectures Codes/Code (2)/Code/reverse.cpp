/* File: reverse.cpp
 *
 * Code to recursively reverse a string.
 */
#include <iostream>
#include <string>
#include "simpio.h"
using namespace std;

string reverseString(string line);

int main() {
	string line = getLine("Enter a string: ");
	cout << reverseString(line) << endl;
}

/* Returns the reverse of the indicated string. */
string reverseString(string line) 
	if (line == "") {
		return "";
	}
	else {
		return reverseString(line.substr(1)) + line[0];
	}
}




