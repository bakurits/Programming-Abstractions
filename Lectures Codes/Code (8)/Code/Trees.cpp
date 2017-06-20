/*
 * File: Trees.cpp
 * ---------------
 * A program that generates trees using recursion!
 */

#include <iostream>
#include "random.h"
#include "gwindow.h"
#include "gobjects.h"
using namespace std;

const double kWindowWidth = 800;
const double kWindowHeight = 400;

/* Branching angle. */
const double kMinAngle = -60;
const double kMaxAngle = +60;

/* Number of branches at each tree. */
const int kMinBranchingFactor = 3;
const int kMaxBranchingFactor = 6;

/* Maximum level of the tree. */
const int kMaxLevel = 9;

void drawTree(GWindow& window, double x, double y, double length, double theta);

/* Main program */
int main11() {
	GWindow window(kWindowWidth, kWindowHeight);
	drawTree(window, window.getWidth() / 2.0, window.getHeight(),
	         window.getHeight(), 90);
	return 0;
}

void recDrawTree(GWindow& window, double x, double y, double length, double theta, int order) {
	/* Drawing an order-0 tree is instantaneous. */
	if (order == 0) return;
	
	/* Draw the tree trunk and remember the endpoint. */
	GPoint endpoint = window.drawPolarLine(x, y, length / 2.0, theta);
	
	/* Determine how many child branches we should have. */
	int numChildren = 5;//randomInteger(kMinBranchingFactor, kMaxBranchingFactor);
	                                
	/* Recursively draw all child branches. */
	for (int i = 0; i < numChildren; i++) {
		recDrawTree(window, endpoint.getX(), endpoint.getY(),
		            length / 2.0,
		            theta + randomReal(kMinAngle, kMaxAngle),
		            order - 1);
	}
}

void drawTree(GWindow& window, double x, double y, double length, double theta) {
	recDrawTree(window, x, y, length, theta, kMaxLevel);
}








