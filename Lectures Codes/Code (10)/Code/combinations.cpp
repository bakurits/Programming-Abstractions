/* File: combinations.cpp
 *
 * A program to list off all combinations of a master set.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "console.h"

using namespace std;

void listCombinationsOf(Set<int> s, int k);

int main() {
	Set<int> masterSet;
	masterSet += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
	
	listCombinationsOf(masterSet, masterSet.size());
}

void recListCombinationsOf(Set<int> s, int k, Set<int> soFar) {
	if (k == 0) {
		cout << soFar << endl;
	} else if (k > s.size()) {
		// Absolutely nothing!!!  HAHAHAHAHAAAA!!!!
	} else {
		int elem = s.first();
		recListCombinationsOf(s - elem, k - 1, soFar + elem);
		recListCombinationsOf(s - elem, k, soFar);
	}
}

void listCombinationsOf(Set<int> s, int k) {
	Set<int> emptySet;
	recListCombinationsOf(s, k, emptySet);
}



