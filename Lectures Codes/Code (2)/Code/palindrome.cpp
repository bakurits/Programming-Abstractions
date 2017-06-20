/* File: palindrome.cpp
 *
 * A program that reads a file of English words, then prints out all
 * the palindromic words.
 */
#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
using namespace std;

bool isPalindrome(string text);

int main() {
	/* Open the file for reading.  We really should check whether
	 * the file is open before proceeding.
	 */
	string file = "dictionary.txt";
	ifstream input(file.c_str());
	
	/* Read each line of the file and print out those that are palindromes. */
	string line;
	while (getline(input, line)) {
		if (isPalindrome(line)) {
			cout << line << endl;
		}
	}
	
	return 0;
}

/* Returns whether the given string is a palindrome. */
bool isPalindrome(string text) {
	if (text.length() < 2) {
		return true;
	}

	return (text[0] == text[text.length() - 1]) && 
		isPalindrome(text.substr(1, text.length() - 2));

	return isPalindrome(text.substr(1, text.length() - 2)) &&
		(text[0] == text[text.length() - 1]);
}