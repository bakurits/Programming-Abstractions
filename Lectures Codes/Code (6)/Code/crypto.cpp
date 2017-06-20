#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "foreach.h"
using namespace std;

/* Crypto system for completely unsafe login. */
struct Crypto {
	map<string, string> users;
	
	Crypto() {
		ifstream input("plaintext-passwords.txt");
		string username, password;
		while (getline(input, username) && getline(input, password)) {
			users[username] = password;
		}
	}
	
	static Crypto& instance() {
		static Crypto theInstance;
		return theInstance;
	}
	
	bool login(string& username, string& password) {
		if (!users.count(username)) return false;
		return users[username] == password;
	}
};

bool login(string& username, string& password) {
	return Crypto::instance().login(username, password);
}
