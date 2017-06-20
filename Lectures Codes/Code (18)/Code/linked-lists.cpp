/*******************************************
 * File: linked-lists.cpp
 *
 * A program that shows off a simple use of
 * linked lists.
 */

#include <iostream>
#include <string>
#include "simpio.h"
using namespace std;

/* Type: Cell
 * A cell in a linked list.
 */
struct Cell {
	string value;
	Cell* next;
};

Cell* readList();
void printList(Cell* list);
void deleteList(Cell* list);

int main3() {
	Cell* list = readList();
	printList(list);
	deleteList(list);
}

Cell* readList() {
	Cell* result = NULL;

	while (true) {
		string line = getLine("Next entry? ");
		if (line == "") break;
		
		Cell* cell = new Cell;
		cell->value = line;
		
		cell->next = result;
		result = cell;
	}
	
	return result;
}

void printList(Cell* list) {
	for (; list != NULL; list = list->next) {
		cout << list->value << endl;
	}
}

void deleteList(Cell* list) {
	// TODO: Fill this in!
}




