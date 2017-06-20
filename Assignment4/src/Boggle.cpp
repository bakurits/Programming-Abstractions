/*
 * File: Boggle.cpp
 * ----------------
 * Name: Bakur Tsutskhashvili
 * Section: Levan Sarchimelia
 * This file is the main starter file for Assignment #4, Boggle.
 */

#include <iostream>
#include <algorithm>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "set.h"

using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const int SMALL_DELAY = 100;
const int DELAY = 500;

const int DICE_SIDES = 6;

const int STANDARD_SIZE = 4;
const int BIG_BOGGLE_SIZE = 5;

const string STANDARD_CUBES[16]  = {
	"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
	"AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
	"DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
	"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string BIG_BOGGLE_CUBES[25]  = {
	"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
	"AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
	"CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
	"DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
	"FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void getDataFromUser(int &N_Rows);
void newGame(int N_Rows, Grid <char> &board, Lexicon &Words);
void fillBoard(int N_Rows, Grid <char> &board);
void fillBoardByUsersString(int N_Rows, Grid <char> &board);
void fillBoardByRandom(int N_Rows, Grid <char> &board);
bool isValidString(string st, int N_Rows);
void humanPlaySimulation(int N_Rows, Grid <char> &board, Lexicon &Words, Set <string> &guessedWords);
bool isValidWord(string word, Lexicon &Words, Set <string> &guessedWords);
bool findRoute(string word, int N_Rows, Grid <char> &board);
Vector < pair <int, int> > getRoute(int row, int col, string word, Grid <bool> &isUsed, Grid <char> &board, int N_Rows);
void highlightRoute(Vector < pair <int, int> > &result);
bool isInBounds(int row, int col, int N_Rows);
void computerPlaySimulation(int N_Rows, Grid <char> &board, Lexicon &Words, Set <string> &guessedWords);
void findEveryWord(string curWord, int row, int col, int N_Rows, Grid <char> &board, Grid <bool> &isUsed, Lexicon &Words, Set <string> &guessedWords);

/* Main program */

int main() {
	// Declaring variables

	int N_Rows; // Size of board
	Grid <char> board;
	Lexicon Words("EnglishWords.dat"); // Stores English words

	//----------------------------------------


	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
	initGBoggle(gw);
	welcome();
	getDataFromUser(N_Rows);
	newGame(N_Rows, board, Words);
	return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
	cout << "Welcome!  You're about to play an intense game ";
	cout << "of mind-numbing Boggle.  The good news is that ";
	cout << "you might improve your vocabulary a bit.  The ";
	cout << "bad news is that you're probably going to lose ";
	cout << "miserably to this little dictionary-toting hunk ";
	cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;

	string instructionIndicator = getLine("Do you need instructions?  ");
	if (toUpperCase(instructionIndicator) == "YES") {
		giveInstructions();
	}
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
	cout << endl;
	cout << "The boggle board is a grid onto which I ";
	cout << "I will randomly distribute cubes. These ";
	cout << "6-sided cubes have letters rather than ";
	cout << "numbers on the faces, creating a grid of ";
	cout << "letters on which you try to form words. ";
	cout << "You go first, entering all the words you can ";
	cout << "find that are formed by tracing adjoining ";
	cout << "letters. Two letters adjoin if they are next ";
	cout << "to each other horizontally, vertically, or ";
	cout << "diagonally. A letter can only be used once ";
	cout << "in each word. Words must be at least four ";
	cout << "letters long and can be counted only once. ";
	cout << "You score points based on word length: a ";
	cout << "4-letter word is worth 1 point, 5-letters ";
	cout << "earn 2 points, and so on. After your puny ";
	cout << "brain is exhausted, I, the supercomputer, ";
	cout << "will find all the remaining words and double ";
	cout << "or triple your paltry score." << endl << endl;
	cout << "Hit return when you're ready...";
	getLine();
}

/*
 * Function: getDataFromUser
 * Usage: getDataFromUser(N_Rows);
 * --------------------------
 * Gets size of board from user
 */

void getDataFromUser(int &N_Rows) {

	cout << "You can choose standard Boggle (4x4 grid)" << endl;
	cout << "or Big Boggle (5x5)." << endl;

	string sizeIndicator = getLine("Would you like Big Boggle?  ");
	N_Rows = (toUpperCase(sizeIndicator) == "YES") ? BIG_BOGGLE_SIZE : STANDARD_SIZE;

	cout << endl;

}

/*
 * Function: newGame
 * Usage: newGame(N_Rows, board, Words);
 * --------------------------
 * This method simulates whole game with new try
 */

void newGame(int N_Rows, Grid <char> &board, Lexicon &Words) {
	while (true) {
		Set <string> guessedWords;

		drawBoard(N_Rows, N_Rows);
		fillBoard(N_Rows, board);
		humanPlaySimulation(N_Rows, board, Words, guessedWords);
		computerPlaySimulation(N_Rows, board, Words, guessedWords);
		string continueIndicator = getLine("Would you like to play again? ");
		if (toUpperCase(continueIndicator) != "YES") break;
	}
}


/*
 * Function: fillBoard
 * Usage: fillBoard(N_Rows, board);
 * --------------------------
 * Fills board with English letters by random choice or users given string
 */

void fillBoard(int N_Rows, Grid <char> &board) {
	 board = Grid <char> (N_Rows, N_Rows);

	 cout << "I'll give you a chance to set up the board to your specification, ";
	 cout << "which makes it easier to confirm your boggle program is working." << endl;
	 string configurationIndicator = getLine("Do you want to force the board configuration? ");

	 if (toUpperCase(configurationIndicator) == "YES") {
		 fillBoardByUsersString(N_Rows, board);
	 } else {
		 fillBoardByRandom(N_Rows, board);
	 }

	 for (int i = 0; i < N_Rows; i++) {
		 for (int j = 0; j < N_Rows; j++) {
			 labelCube(i, j, board[i][j]);
		 }
	 }

}

/*
 * Function: fillBoardByUsersString
 * Usage: fillBoardByUsersString(N_Rows, board);
 * --------------------------
 * This method fills board from given string
 */

void fillBoardByUsersString(int N_Rows, Grid <char> &board) {
	cout << "Enter a " << N_Rows * N_Rows << "-character string to identify ";
	cout << "which letters you want on the cubes." << endl;
	cout << "The first " << N_Rows << " letters are the cubes on the top row from left to right, ";
	cout << "the next " << N_Rows << " letters are the second row, and so on. " << endl;
	string givenString;

	while (true) {
		givenString = getLine("Enter the string: ");
		givenString = toUpperCase(givenString);
		if (isValidString(givenString, N_Rows)) break;
		cout << "This string is't valid" << endl;
		cout << "Please enter " << N_Rows * N_Rows << " English alphabet letter" << endl;
	}

   for (int i = 0; i < givenString.length(); i++) {
	   board[i / N_Rows][i % N_Rows] = givenString[i];
   }

}

/*
 * Function: fillBoardByRandom
 * Usage: fillBoardByRandom(N_Rows, board);
 * --------------------------
 * This method fills board using random shuffling of predetermined array
 */

void fillBoardByRandom(int N_Rows, Grid <char> &board) {
	Vector <string> rndVector;
	for (int i = 0; i < N_Rows * N_Rows; i++) {
		if (N_Rows == STANDARD_SIZE) {
			rndVector.add(STANDARD_CUBES[i]);
		} else {
			rndVector.add(BIG_BOGGLE_CUBES[i]);
		}
	}

	for (int i = 0; i < rndVector.size(); i++) {
		int rnd = randomInteger(i, rndVector.size() - 1);
		swap(rndVector[i], rndVector[rnd]);
	}

	for (int i = 0; i < rndVector.size(); i++) {
		int rnd = randomInteger(0, DICE_SIDES - 1);
		board[i / N_Rows][i % N_Rows] = rndVector[i][rnd];
	}

}

/*
 * Function: isValidString
 * Usage: isValidString(st, N_Rows);
 * --------------------------
 * This method checks if user given string is valid for fill the board
 */

bool isValidString(string st, int N_Rows) {
	if (st.length() != N_Rows * N_Rows) return false;

	for (int i = 0; i < st.length(); i++) {
		if (st[i] < 'A' || st[i] > 'Z') {
			 return false;
		}
	}
	return true;
}

/*
 * Function: playSimulation
 * Usage: playSimulation(N_Rows, board, Words);
 * --------------------------
 * This method handles human play simulation
 */

void humanPlaySimulation(int N_Rows, Grid <char> &board, Lexicon &Words, Set <string> &guessedWords) {

	cout << "Ok, take all the time you want and find all the words you can!";
	cout << "  Signal that you're finished by entering an empty line." << endl;

	while (true) {
		string curWord = getLine("Enter a word: ");
		if (curWord.length() == 0) break;
		if (isValidWord(curWord, Words, guessedWords)) {
			if (findRoute(curWord, N_Rows, board)) {
				guessedWords.add(curWord);
				recordWordForPlayer(curWord, HUMAN);
			}
		}
	}
}

/*
 * Function: isValidWord
 * Usage: isValidWord(word, Words, guessedWords);
 * --------------------------
 * This method checks if players given word is valid
 */

bool isValidWord(string word, Lexicon &Words, Set <string> &guessedWords) {
	if (word.length() < 4) {
		cout << "I'm sorry, but we have our standards." << endl;
		cout << "That word doesn't meet the minimum word length." << endl;
		return false;
	}

	if (!Words.contains(word)) {
		cout << "That's not a word!" << endl;
		return false;
	}

	if (guessedWords.contains(word)) {
		cout << "You've already guessed that!" << endl;
		return false;
	}
	return true;
}

/*
 * Function: findRoute
 * Usage: findRoute(word, N_Rows, board);
 * --------------------------
 * This method checks if players given word is present in board
 */

bool findRoute(string word, int N_Rows, Grid <char> &board) {
	Grid <bool> isUsed(N_Rows, N_Rows);
	Vector < pair<int, int> > result;

	for (int i = 0; i < N_Rows; i++) {
		word = toUpperCase(word);
		for (int j = 0; j < N_Rows; j++) {
			if (result.size() == 0) {
				result = getRoute(i, j, word, isUsed, board, N_Rows);
			}
		}
	}

	if (result.size() > 0) {
		reverse(result.begin(), result.end());
		highlightRoute(result);
		return true;
	} else {
		return false;
	}
}

/*
 * Function: getRoute
 * Usage: getRoute(row, col, word, isUsed, board, N_Rows);
 * --------------------------
 * This method finds route for given string
 */

Vector < pair <int, int> > getRoute(int row, int col, string word, Grid <bool> &isUsed, Grid <char> &board, int N_Rows) {
	Vector < pair <int, int> > result;
	if (!isInBounds(row, col, N_Rows)) return result;
	if (isUsed[row][col] || word[0] != board[row][col]) return result;

	if (word.length() == 1) {
		result.add(make_pair(row, col));
		return result;
	}

	isUsed[row][col] = true;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			Vector < pair <int, int> > neighbourResult = getRoute(row + i, col + j, word.substr(1), isUsed, board, N_Rows);
			if (neighbourResult.size() > 0) {
				result = neighbourResult; result.add(make_pair(row, col));
				break;
			}
		}
	}

	isUsed[row][col] = false;
	return result;
}

/*
 * Function: highlightRoute
 * Usage: highlightRoute(result);
 * --------------------------
 * This method displays highlighted route
 */

void highlightRoute(Vector < pair <int, int> > &result) {
	for (int i = 0; i < result.size(); i++) {
		highlightCube(result[i].first, result[i].second, true);
		pause(SMALL_DELAY);
	}

	pause(DELAY);

	for (int i = 0; i < result.size(); i++) {
		highlightCube(result[i].first, result[i].second, false);
	}
}

/*
 * Function: isInBounds
 * Usage: isInBounds(row, col, N_Rows);
 * --------------------------
 * This method checks is current cell is in bounds
 */

bool isInBounds(int row, int col, int N_Rows) {
	if (row < 0 || row >= N_Rows) return false;
	if (col < 0 || col >= N_Rows) return false;
	return true;
}

/*
 * Function: computerPlaySimulation
 * Usage: computerPlaySimulation(N_Rows, board, Words, guessedWords);
 * --------------------------
 * This method simulates computer play
 */

void computerPlaySimulation(int N_Rows, Grid <char> &board, Lexicon &Words, Set <string> &guessedWords) {
	Grid <bool> isUsed(N_Rows, N_Rows);
	for (int i = 0; i < N_Rows; i++) {
		for (int j = 0; j < N_Rows; j++) {
			string initialWord = "";
			initialWord += board[i][j];
			findEveryWord(initialWord, i, j, N_Rows, board, isUsed, Words, guessedWords);
		}
	}
}

/*
 * Function: findEveryWord
 * Usage: findEveryWord(curWord, row, col, N_Rows, board, isUsed, Words, guessedWords);
 * --------------------------
 * This method finds every word which presents on board
 */

void findEveryWord(string curWord, int row, int col, int N_Rows, Grid <char> &board, Grid <bool> &isUsed, Lexicon &Words, Set <string> &guessedWords) { 
	if (curWord.length() > 3 && Words.contains(curWord) && !guessedWords.contains(curWord)) {
		guessedWords.add(curWord);
		recordWordForPlayer(curWord, COMPUTER);
	}

	isUsed[row][col] = true;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int newRow = row + i;
			int newCol = col + j;
			if (isInBounds(newRow, newCol, N_Rows) && !isUsed[newRow][newCol] && Words.containsPrefix(curWord + board[newRow][newCol])) {
				findEveryWord(curWord + board[newRow][newCol], newRow, newCol, N_Rows, board, isUsed, Words, guessedWords);
			}
		}
	}
	
	isUsed[row][col] = false;
}
