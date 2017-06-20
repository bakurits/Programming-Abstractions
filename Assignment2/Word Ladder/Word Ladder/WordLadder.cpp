/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: Bakur Tsutskhasvhili
 * Section: Levan Sarchimelia
 * This file is the starter project for the Word Ladder problem.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "vector.h"
#include "queue.h"
#include "set.h"
#include "map.h"

using namespace std;

const string FILENAME = "EnglishWords.dat";
const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

/**
 * This method initializes program
 * Adds words in dictionary from file
 */
void init(Lexicon &dictionary);


/**
 * This method handles whole process
 */
void process(Lexicon &dictionary);


/**
 * This method find ladder for current start end end words
 * If result vector is empty than ladder doesn't exists;
 */
void get_ladder(Lexicon &dictionary, string &start_word, string &end_word, Vector <string> &result);


/**
 * This method checks if new generated word is in dictionary
 * And if its true adds in queue
 */
void add_in_queue(Lexicon &dictionary, Set <string> &used_words, Queue<string> &word_queue, Map<string, string> &generated_from, string &cur_word, string &new_word);


/**
 * This method restores path from generated_from Map
 */
void get_reversed_path(Set <string> &used_words, Map<string, string> &generated_from, string &end_word, string &start_word, Vector<string> &result);


/**
 * This method prints ladder if it exists
 * Or "No ladder found" otherwise
 */
void print_ladder(Vector <string> &ladder);


int main() {
	// Declaring variables
	
	Lexicon dictionary;
	// ---------------------------------

	init(dictionary);
	process(dictionary);

    return 0;
}


void init(Lexicon &dictionary) {
	dictionary.addWordsFromFile(FILENAME);
}


void process(Lexicon &dictionary) {
	
	while (true) {
		string start_word, end_word;

		start_word = getLine("Enter start word (Or nothing to quit) : ");

		if (start_word.length() == 0) break;

		end_word = getLine("Enter destination word : ");

		cout << "Please wait ..." << endl;

		Vector <string> ladder;

		get_ladder(dictionary, start_word, end_word, ladder);

		print_ladder(ladder);
		cout << endl;

	}

}


void get_ladder(Lexicon &dictionary, string &start_word, string &end_word, Vector <string> &result) {
	
	Queue <string> word_queue;
	Map<string, string> generated_from;
	Set <string> used_words;

	word_queue.enqueue(start_word);
	used_words.add(start_word);

	while (!word_queue.isEmpty()) {
		string cur_word = word_queue.dequeue();
		if (cur_word == end_word) {
			get_reversed_path(used_words, generated_from, end_word, start_word, result);
			reverse(result.begin(), result.end());
			break;
		}

		for (int i = 0; i < cur_word.length(); i++) {
			for (int j = 0; j < ALPHABET.length(); j++) {
				string new_string = cur_word.substr(0, i) + ALPHABET[j] + cur_word.substr(i + 1, cur_word.length() - i - 1);
				add_in_queue(dictionary, used_words, word_queue, generated_from, cur_word, new_string);
			}
		}
	}
}


void add_in_queue(Lexicon &dictionary, Set <string> &used_words, Queue<string> &word_queue, Map<string, string> &generated_from, string &cur_word, string &new_word) {
	if (dictionary.contains(new_word) && !used_words.contains(new_word)) {
		used_words.add(new_word);
		word_queue.enqueue(new_word);
		generated_from.put(new_word, cur_word);
	}
}


void get_reversed_path(Set <string> &used_words, Map<string, string> &generated_from, string &end_word, string &start_word, Vector<string> &result) {
	if (used_words.contains(end_word)) {
		string cur_word = end_word;
		while (cur_word != start_word) {
			result.add(cur_word);
			cur_word = generated_from.get(cur_word);
		}
		result.add(start_word);
	}
}


void print_ladder(Vector <string> &ladder){
	if (ladder.size() > 0) {
			cout << "Found ladder: ";
			for (int i = 0; i < ladder.size(); i++) {
				cout << ladder[i];
				if (i < ladder.size() - 1) cout << " -> ";
			}
			cout << endl;
	} else {
			cout << "No ladder found." << endl;
	}
}