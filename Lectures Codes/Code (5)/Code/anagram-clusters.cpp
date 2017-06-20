/* File: anagram-clusters.cpp
 *
 * A program that clusters words into anagram clusters
 * to let the user find all anagrams of a word.
 */
#include <iostream>
#include <string>
#include "lexicon.h"
#include "simpio.h"
#include "map.h"
#include "set.h"
using namespace std;

string sort(string& word) {
	Map<char, int> frequencies;
	foreach (char ch in word) {
		frequencies[ch]++;
	}
	
	string result;
	foreach (char ch in frequencies) {
		for (int i = 0; i < frequencies[ch]; i++) {
			result += ch;
		}
	}
	
	return result;
}

int main() {
	Lexicon words("EnglishWords.dat");
	Map<string, Set<string> > clusters;
	
	foreach(string word in words) {
		// Sort the letters of the word
		// Update cluster containing it.
		clusters[sort(word)] += word;
	}
	
	while (true) {
		string word = getLine("Enter a word: ");
		if (word == "") break;
		
		if (clusters.containsKey(sort(word))) {
			foreach (string anagram in clusters[sort(word)]) {
				cout << anagram << endl;
			}
		} else {
			cout << ":-(" << endl;
		}
	}
}







		
	
