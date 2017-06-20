/* File: cell-towers.cpp
 *
 * A program that determines the maximum population that can be covered
 * by purchasing cell towers with a single transmitting frequency.
 */
#include <iostream>
#include <algorithm>
#include "vector.h"
using namespace std;

int totalOf(Vector<int>& list) {
	int result = 0;
	for (int i = 0; i < list.size(); i++) {
		result += list[i];
	}
	return result;
}

Vector<int> tailOf(Vector<int>& list) {
	Vector<int> result = list;
	result.removeAt(0);
	return result;
}

int maximumCoverageFor(Vector<int>& populations) {
	if (populations.size() == 0) {
		return 0;
	} else if (populations.size() == 1) {
		return populations[0];
	} else {
		Vector<int> allButFirst    = tailOf(populations);
		Vector<int> allButFirstTwo = tailOf(allButFirst);
		
		return max(maximumCoverageFor(allButFirst),
		           populations[0] + maximumCoverageFor(allButFirstTwo));
	}
}

int main() {
	Vector<int> populations;
	for (int i = 0; i < 40; i++) {
		populations += i;
	}
	
	cout << "Maximum coverage: " << maximumCoverageFor(populations) << endl;
	cout << "Total population: " << totalOf(populations) << endl;

	return 0;
}


