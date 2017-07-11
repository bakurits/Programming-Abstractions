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


Vector<Loc> shortestPath(Loc start,
			 			 Loc end,
			 			 Grid<double>& world,
			 			 double costFn(Loc from, Loc to, Grid<double>& world)) {
	
	int N_Rows = world.numRows();  int N_Cols = world.numCols();

	Grid<Node> nodesCondition(N_Rows, N_Cols);
	TrailblazerPQueue <Loc> minDistQueue;

	prepareInitialState(world, nodesCondition, minDistQueue, N_Rows, N_Cols, start);

	while (!minDistQueue.isEmpty()) {
		Loc curNode = minDistQueue.dequeueMin();
		nodesCondition[curNode.row][curNode.col].color = GREEN; 
		colorCell(world, curNode, GREEN);
		
		if (curNode == end) break;
		neighbourCheck(world, nodesCondition, minDistQueue, curNode, costFn);
	}

	if (nodesCondition[end.row][end.col].color != GREEN) 
		error("There is no route from start to end.");
	else
		return getRoute(nodesCondition, start, end);
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
				int newLocRow = curRow + vy;	int newLocCol = curCol + vx;
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

Vector <Loc> getRoute(Grid<Node> &nodesCondition, Loc start, Loc end) {
	Vector<Loc> result;
	Loc curLoc = end;
	while (curLoc != makeLoc(-1, -1)) {
		result.add(curLoc);
		curLoc = nodesCondition[curLoc.row][curLoc.col].parent;
	}
	
	for (int i = 0; i < result.size(); i++) {
		if (i < result.size() - i - 1) swap(result[i], result[result.size() - i - 1]);
	}
}