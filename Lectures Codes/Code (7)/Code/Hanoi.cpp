/*
 * File: Hanoi.cpp
 * ---------------
 * This program solves the Tower of Hanoi puzzle.
 */

#include <iostream>
#include "ghanoi.h"    // Animation routines.
#include "gwindow.h"
using namespace std;

/* Constants */

const int N_DISKS = 5;

/* Moves n disks from the start spindle to the destination spindle,
 * using the given spindle as a temporary.
 */
void moveTower(int n, char start, char finish, char temp);


int main3() {
	initHanoiDisplay(N_DISKS);
	moveTower(N_DISKS, 'a', 'c', 'b');
	return 0;
}

/*
 * Function: moveTower
 * Usage: moveTower(n, start, finish, temp);
 * -----------------------------------------
 * Moves a tower of size n from the start spire to the finish
 * spire using the temp spire as the temporary repository.
 */

void moveTower(int n, char start, char finish, char temp) {
   if (n == 1) {
      moveSingleDisk(start, finish);
   } else {
      moveTower(n - 1, start, temp, finish);
      moveSingleDisk(start, finish);
      moveTower(n - 1, temp, finish, start);
   }
}
