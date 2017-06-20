/*
 * File: Warmup.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This program generates a hash code based on user's name.
 * As given, this code has two compiler errors you need to track down 
 * and fix in order to get the program up and running.
 * [Originally written by Julie Zelenski]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "grid.h"
using namespace std;

enum position {
	cross = 1,
	neither = 0,
	nought = -1
};

bool isAllThatKind(Grid <position> &board, int N, int startX, int startY, int incX, int incY, position pos) {
	int curX = startX; int curY = startY;
	while (curX >= 0 && curX < N && curY >= 0 && curY < N) {
		if (board[curX][curX] != pos) return false;
		curX += incX;
		curY += incY;
	}
	
	return true;
}

bool doesPlayerWin(Grid <position> &board, position &player) {
	
	int N = board.nRows;

	for (int i = 0; i < N; i++) {
		
		if (isAllThatKind(board, N, i, 0, 0, 1, cross)) { player = cross; return true; }

		if (isAllThatKind(board, N, 0, i, 1, 0, cross)) { player = cross; return true; }

		if ((i == 0 || i == 2) && isAllThatKind(board, N, 0, i, 1, 1 - i, cross)) { player = cross; return true; }
		

		if (isAllThatKind(board, N, i, 0, 0, 1, nought)) { player = nought; return true; }

		if (isAllThatKind(board, N, 0, i, 1, 0, nought)) { player = nought; return true; }

		if ((i == 0 || i == 2) && isAllThatKind(board, N, 0, i, 1, 1 - i, nought)) { player = nought; return true; }
	}

	return true;

}

int main() {
	
	Grid <position> a;
	a.resize(3);
	
	

    return 0;
}
