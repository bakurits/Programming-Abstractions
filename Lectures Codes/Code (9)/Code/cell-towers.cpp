/* File: cell-towers.cpp
 *
 * Some sample code showing off basic Vector operations.
 */
#include <iostream>
#include <algorithm> // For max
#include "vector.h"
#include "map.h"
#include "console.h"
using namespace std;

Vector<int> tailOf(Vector<int> v) {
	v.remove(0);
	return v;
}

int maximizeCellCoverage(Vector<int> populations,
						 Map<int,int> &solutions) {
	if (populations.size() == 0) {
		return 0;
	}
	else if (populations.size() == 1) {
		return populations[0];
	}
	else if (solutions.containsKey(populations.size())) {
		return solutions[populations.size()];
	}
	else {	
		Vector<int> allButFirst = tailOf(populations);
		Vector<int> allButFirstTwo = tailOf(allButFirst);

		int result =
			max(maximizeCellCoverage(allButFirst,solutions),
				populations[0] + maximizeCellCoverage(allButFirstTwo,solutions));
		solutions[populations.size()] = result;
	 	return result;
	}
}
int main() {
	Vector<int> populations;
	for (int i = 0; i < 1000; i++)
		populations += i;
	
	Map<int,int> solutions;
	cout << "Maximum amount: "
	     << maximizeCellCoverage(populations,solutions) << endl;
	
	return 0;
}






