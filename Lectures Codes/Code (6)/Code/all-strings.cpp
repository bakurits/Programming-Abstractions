#include <iostream>
#include <string>
#include "simpio.h"
#include "queue.h"
#include "crypto.h"
#include "console.h"
using namespace std;

int main() {
	string username = getLine("Enter username: ");

	Queue<string> worklist;
	worklist.enqueue("");
	
	while (!worklist.isEmpty()) {
		string current = worklist.dequeue();
		if (login(username, current)) {
			cout << "Success!  The password is " << current << endl;
			break;
		}
		
		for (char ch = 'a'; ch <= 'z'; ch++) {
			worklist.enqueue(current + ch);
		}
	}
	
	return 0;
}





		
	
