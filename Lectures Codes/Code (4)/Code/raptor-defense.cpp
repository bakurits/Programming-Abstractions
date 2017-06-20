//
//  raptor-defense.cpp
//  BlankProject
//
//  Created by Aubrey Gress on 6/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "grid.h"
#include "random.h"

using namespace std;

void ClearGrid(Grid<bool> &grid);
void PlaceRaptors(Grid<bool> &raptorGrid, int numRaptorsToPlace);
bool IsSafe(Grid<bool> &raptorGrid,int row, int col);
bool HasSafeCells(Grid<bool> &raptorGrid);
int CountRaptors(Grid<bool> raptorGrid);

const int kRaptorGridSize = 10;
const int kNumRaptors = 10;

int main3() {
    Grid<bool> raptorLocations(kRaptorGridSize,kRaptorGridSize);
    ClearGrid(raptorLocations);
    if (CountRaptors(raptorLocations) != 0) {
        cout << "Error: Raptor board not cleared" << endl;
    }
    PlaceRaptors(raptorLocations,kNumRaptors);
    if (CountRaptors(raptorLocations) != kNumRaptors) {
        cout << "Error: Incorrect number of raptors on board!" << endl;
    }
    if (HasSafeCells(raptorLocations)) {
        cout << "You are safe!" << endl;
    } else {
        cout << "Raptors ate you =(" << endl;
    }
    return 0;
}

int CountRaptors(Grid<bool> raptorGrid)
{
    int numRaptors = 0;
    for (int i = 0; i < raptorGrid.numRows(); i++) {
        for (int j = 0; j < raptorGrid.numCols(); j++) {
            if (raptorGrid[i][j]) {
                numRaptors++;
            }
        }
    }
    return numRaptors;
}

bool IsDirectionSafe(Grid<bool> raptorGrid,int row,int col, int dRow, int dCol) {
    row += dRow;
    col += dCol;
    while (raptorGrid.inBounds(row, col)) {
        if (raptorGrid[row][col]) {
            return false;
        }
        row += dRow;
        col += dCol;
    }
    return true;
}

bool IsSafe(Grid<bool> &raptorGrid,int row, int col) {
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            if (dRow != 0 && dCol != 0) {
                bool directionSafe = IsDirectionSafe(raptorGrid,row,col,dRow,dCol);
                if (!directionSafe)
                    return false;
            }
        }
    }
    return true;
}

bool HasSafeCells(Grid<bool> &raptorGrid) {
    for (int row = 0; row < raptorGrid.numRows(); row++) {
        for (int col = 0; col < raptorGrid.numCols(); col++) {
            if (IsSafe(raptorGrid,row,col)) {
                return true;
            }
        }
    }
    return false;
}

void PlaceRaptors(Grid<bool> &raptorGrid, int numRaptorsToPlace)
{
    while (numRaptorsToPlace > 0) {
        int row = randomInteger(0, raptorGrid.numRows()-1);
        int col = randomInteger(0, raptorGrid.numCols()-1);
        if (!raptorGrid[row][col]) {
            raptorGrid[row][col] = true;
            numRaptorsToPlace--;
        }
    }
}

void ClearGrid(Grid<bool> &grid)
{
    for (int i = 0; i < grid.numCols(); i++) {
        for (int j = 0; j < grid.numRows(); j++) {
            grid[i][j] = false;
        }
    }
}