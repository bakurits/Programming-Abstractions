/* File: shrinkable-words.cpp
 *
 * A program to list off all shrinkable words in English.
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "console.h"
using namespace std;

bool isShrinkableWord(string word, Lexicon& lex);

const int kMinimumWordLength = 9;

int main() {
	Lexicon words("EnglishWords.dat");
	
	foreach (string word in words) {
		if (word.length() >= kMinimumWordLength &&
		    isShrinkableWord(word, words)) {
			cout << word << endl;
		}
	}
}

bool isShrinkableWord(string word, Lexicon& lex) {
	if (!lex.contains(word)) return false;
	if (word.length() == 1)  return true;
	
	for (int i = 0; i < word.length(); i++) {
		if (isShrinkableWord(word.substr(0, i) + word.substr(i + 1), lex)) {
			return true;                   
		}
	}
	
	return false;
}








