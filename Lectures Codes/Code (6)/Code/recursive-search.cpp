#include <iostream>
#include <string>
#include "simpio.h"
#include "crypto.h"
#include "console.h"
using namespace std;

void generate(string soFar, int maxDepth) {
	cout << soFar << endl;
	
	if (soFar.length() < maxDepth) {
		for (char ch = 'a'; ch <= 'z'; ch++) {
			generate(soFar + ch, maxDepth);
		}
	}
}

int main() {
	generate("", 5);
	return 0;
}



		
	
