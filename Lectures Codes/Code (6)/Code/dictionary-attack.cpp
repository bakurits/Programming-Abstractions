#include <iostream>
#include <string>
#include "simpio.h"
#include "lexicon.h"
#include "crypto.h"
#include "console.h"
using namespace std;

int main() {
	Lexicon words("EnglishWords.dat");
	string username = getLine("Enter username: ");
	
	foreach (string word in words) {
		if (login(username, word)) {
			cout << "Password broken!  It was " << word << endl;
			break;
		}
	}
	
	return 0;
}





		
	
