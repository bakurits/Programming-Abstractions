/* File: permutations.cpp
 *
 * A program to list off all permutations of a master set.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
using namespace std;

/* This version of the function returns a Vector holding all
 * permutations of the string.
 */
Vector<string> permutationsOf(string s);

/* This function prints out the permutations of the string one
 * after another.
 */
void listPermutationsOf(string s);

int main() {
	listPermutationsOf("UNCOPYRIGHTABLE");
}

/* Given a string, returns a Vector holding all permutations
 * of that string.
 */
Vector<string> permutationsOf(string s) {
	Vector<string> result;
	
	/* Base case: If there are no characters in the string, the only permutation
	 * of the string is the string itself.
	 */
	if (s == "") {
		result += "";
		return result;
	}
	/* Recursive step: For each character in the string, try removing that
	 * character, generating all other permutations recursively, then snapping
	 * that string back into place.
	 */
	else {
		for (int i = 0; i < s.length(); i++) {
			Vector<string> v = permutationsOf(s.substr(0, i) + s.substr(i + 1));
			foreach (string permutation in v) {
			 	result += s[i] + permutation;        
			}
		}
		return result;
	}
}

/* Recursive function that lists, but does not process, each string. */
void recListPermutationsOf(string &s, string &soFar) {
	if (s == "") {
		cout << soFar << endl;
	}
	else {
		for (int i = 0; i < s.length(); i++) {
			soFar = soFar + s[i];
			s = s.substr(0, i) + s.substr(i + 1);
			recListPermutationsOf(s, soFar);
		}
	}
}

void listPermutationsOf(string s) {
	string s1 = "";
	recListPermutationsOf(s, s1);
}







