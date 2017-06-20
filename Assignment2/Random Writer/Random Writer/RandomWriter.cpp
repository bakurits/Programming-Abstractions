/*
 * File: RandomWriter.cpp
 * ----------------------
 *	Name: Bakur Tsutskhashvili
 *	Section: Levan Sarchimelia
 *	This file is the starter project for the Random Writer problem.
 */


#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "console.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"


using namespace std;

const int GENERATED_TEXT_LENGTH = 2000; // length of generated text

/**
 * This method collects information from user
 * Gets text and "K" for algorithm
 */
void Get_Info_From_User(string &text, int &K);


/**
 * This method processes data
 * Counts frequency of K-lengthed substrings and finds most frequent one
 * Collects symbols after every K-lengthed substring
 */
void Data_Process(string &text, int K, string &Most_Frequent_Substring, Map <string, Vector <char> > &Symbols_After_K_Lengthed_Substring);


/**
 * This method generates new text from collected data
 */
string Generated_Text(int K, string &Starting_String, Map <string, Vector <char> > &Symbols_After_K_Lengthed_Substring);

int main() {

	// Declaring variables

	string text; // Whole texts as string
	int K; // Markov order's length
	string Most_Frequent_Substring; // Most frequent K-lengthed substring
	Map <string, Vector <char> > Symbols_After_K_Lengthed_Substring; // Stores next symbols for every K-lengthed substring
	// --------------------------------------------------------



	Get_Info_From_User(text, K);
	Data_Process(text, K, Most_Frequent_Substring, Symbols_After_K_Lengthed_Substring);

	cout << Generated_Text(K, Most_Frequent_Substring, Symbols_After_K_Lengthed_Substring);

	return 0;
}


void Get_Info_From_User(string &text, int &K) {
	ifstream file; // file
	while (true) {
		string filename = getLine("Enter the source text : ");
		file.open(filename.c_str());
		if (file.is_open()) break;
		file.clear();
		cout << "Unable to open that file. Try again." << endl;
	}

	while (true) {
		cout << "Enter the Markov order [1-10] : ";
		K = getInteger();
		if (K > 0 && K < 11) break;
		cout << "That value is out of range." << endl;
	}

	while (file.good())  text += file.get();

	cout << "Processing file ..." << endl;
}


void Data_Process(string &text, int K, string &Most_Frequent_Substring, Map <string, Vector <char> > &Symbols_After_K_Lengthed_Substring) {

	Map <string, int> K_Lengthed_Substring_Frequency;

	for (int i = 0; i + K - 1 < text.length(); i++) {
		K_Lengthed_Substring_Frequency[text.substr(i, K)]++;
		if (i + K < text.length()) {
			Symbols_After_K_Lengthed_Substring[text.substr(i, K)].add(text[i + K]);
		}
	}

	foreach (string st in K_Lengthed_Substring_Frequency) {
		if (Most_Frequent_Substring.length() == 0 || K_Lengthed_Substring_Frequency[Most_Frequent_Substring] < K_Lengthed_Substring_Frequency[st]) {
			Most_Frequent_Substring = st;
		}
	}
}


string Generated_Text(int K, string &Starting_String, Map <string, Vector <char> > &Symbols_After_K_Lengthed_Substring) {
	string res = Starting_String;

	while (res.length() < GENERATED_TEXT_LENGTH) {
		int Rand_Index = randomInteger(0, Symbols_After_K_Lengthed_Substring[res.substr(res.length() - K, K)].size() - 1);

		if (Rand_Index < 0) return res;

		res = res + Symbols_After_K_Lengthed_Substring[res.substr(res.length() - K, K)][Rand_Index];
	}

	return res;
}
