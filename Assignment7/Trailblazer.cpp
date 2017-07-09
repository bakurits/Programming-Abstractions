/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
using namespace std;

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
Vector<Loc> shortestPath(Loc start,
			 			 Loc end,
			 			 Grid<double>& world,
			 			 double costFn(Loc from, Loc to, Grid<double>& world)) {
	
	int N_Rows = word.numRows();  int N_Cols = word.numCols();

	Grid<Node> nodesCondition(N_Rows, N_Cols);
	TrailblazerPQueue <Loc> minDistQueue;

	prepareInitialState(world, nodesCondition, minDistQueue, N_Rows, N_Cols, start);

	while (!minDistQueue.isEmpty()) {
		Loc curNode = minDistQueue.dequeue();
		nodesCondition[curNode.row][curNode.col].color = GREEN; colorCell(world, curNode, GREEN);
		if (curNode == end) break;
		neighbourCheck(world, nodesCondition, minDistQueue, curNode);
	}
	error("shortestPath is not implemented yet.");
}

Set<Edge> createMaze(int numRows, int numCols) {
	error("createMaze is not implemented yet.");
}

void prepareInitialState(Grid<double>& world, 
						 Grid<Node> &nodesCondition, 
						 TrailblazerPQueue<Loc> &minDistQueue, 
						 int N_Rows, 
						 int N_Cols, 
						 Loc start) {
	
	for (int i = 0; i < N_Rows; i++) {
		for (int j = 0; j < N_Cols; j++) {
			nodesCondition[i][j].color = GRAY;
			nodesCondition[i][j].location = makeLoc(i, j);
			nodesCondition[i][i].parent = makeLoc(-1, -1);
			colorCell(world, nodesCondition[i][j].location, GRAY);
		}
	}

	colorCell(world, start, YELLOW);
	nodesCondition[start.row][start.col].dist = 0;
	minDistQueue.enqueue(start, 0);

}

void neighbourCheck(Grid<double>& world, 
					Grid<Node> &nodesCondition, 
					TrailblazerPQueue<Loc> &minDistQueue, 
					Loc curLocation,
					double costFn(Loc from, Loc to, Grid<double>& world)) {
	int curRow = curLocation.row; int curCol = curLocation.col;
	for (int vx = -1; vx <= 1; vx++) {
			for (int vy = -1; vy <= 1; vy++) {
				newLocRow = curRow + vy;	newLocCol = curCol + vx;
				double EdgeCost = costFn(curLocation, makeLoc(newLocRow, newLocCol), world);
				if (nodesCondition[newLocRow][newLocCol].color == GRAY) {
					nodesCondition[newLocRow][newLocCol].color = YELLOW;
					nodesCondition[newLocRow][newLocCol].dist = nodesCondition[curRow][curCol].dist + EdgeCost;
					nodesCondition[newLocRow][newLocCol].parent = curLocation;
				} else {
					if (nodesCondition[newLocRow][newLocCol].color == YELLOW &&
						nodesCondition[newLocRow][newLocCol].dist > nodesCondition[curRow][curCol].dist + EdgeCost) {
							nodesCondition[newLocRow][newLocCol].dist = nodesCondition[curRow][curCol].dist + EdgeCost;
							nodesCondition[newLocRow][newLocCol].parent = curLocation;
							minDistQueue.decreaseKey(makeLoc(newLocRow, newLocCol), nodesCondition[newLocRow][newLocCol].dist);
						}
				}
			}
		}
}
