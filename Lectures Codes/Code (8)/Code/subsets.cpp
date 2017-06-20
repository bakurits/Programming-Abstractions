/* File: subsets.cpp
 *
 * A program to list off all subsets of a master set.
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

Vector<Set<int> > subsetsOf(Set<int> masterSet);
void visitSubsets(Set<int> soFar, Set<int> remaining);
int main8() {
	Set<int> masterSet;
	masterSet += 1, 2, 3, 4, 5;
/*
	foreach (Set<int> subset in subsetsOf(masterSet)) {
		cout << subset << endl;
	}	
*/
	Set<int> soFar;
	visitSubsets(soFar,masterSet);
	return 0;
}

Vector<Set<int> > subsetsOf(Set<int> masterSet) {
	Vector<Set<int> > results;
	if (masterSet.size() == 0) {
		Set<int> emptySet;
		results.add(emptySet);
		return results;
	}
	int x = masterSet.first();
	Vector<Set<int> > v = 
		subsetsOf(masterSet - x);
	results = v;
	for(int i = 0; i < v.size(); i++) {
		Set<int> copy = v[i];
		results.add(copy + x);
	}
	return results;
}

void visitSubsets(Set<int> soFar, 
				  Set<int> remaining) {
	if (remaining.size() == 0)
		cout << soFar << endl;
	else {
		int x = remaining.first();
		visitSubsets(soFar+x,remaining-x);
		visitSubsets(soFar,remaining-x);
	}
}

