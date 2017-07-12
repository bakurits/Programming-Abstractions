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
						 Grid<double> &world,
						 double costFn(Loc from, Loc to, Grid<double> &world))
{

	int N_Rows = world.numRows();
	int N_Cols = world.numCols();

	Grid<Node> nodes(N_Rows, N_Cols);
	TrailblazerPQueue<Loc> minDistQueue;

	prepareInitialState(world, nodes, minDistQueue, N_Rows, N_Cols, start);

	while (!minDistQueue.isEmpty())
	{
		Loc curNode = minDistQueue.dequeueMin();
		nodes[curNode.row][curNode.col].color = GREEN;
		colorCell(world, curNode, GREEN);

		if (curNode == end)
			break;
		neighbourCheck(world, nodes, minDistQueue, curNode, costFn);
	}

	if (nodes[end.row][end.col].color != GREEN)
		error("There is no route from start to end.");
	else
		return getRoute(nodes, start, end);
}

Set<Edge> createMaze(int numRows, int numCols)
{
	error("createMaze is not implemented yet.");
	Set<Edge> a;
	return a;
}

void prepareInitialState(Grid<double> &world,
						 Grid<Node> &nodes,
						 TrailblazerPQueue<Loc> &minDistQueue,
						 int N_Rows,
						 int N_Cols,
						 Loc start)
{

	for (int i = 0; i < N_Rows; i++)
	{
		for (int j = 0; j < N_Cols; j++)
		{
			nodes[i][j].color = GRAY;
			nodes[i][j].location = makeLoc(i, j);
			nodes[i][j].parent = makeLoc(-1, -1);
			colorCell(world, nodes[i][j].location, GRAY);
		}
	}

	colorCell(world, start, YELLOW);
	nodes[start.row][start.col].dist = 0;
	minDistQueue.enqueue(start, 0);
}

void neighbourCheck(Grid<double> &world,
					Grid<Node> &nodes,
					TrailblazerPQueue<Loc> &minDistQueue,
					Loc curLocation,
					double costFn(Loc from, Loc to, Grid<double> &world))
{

	int curRow = curLocation.row;
	int curCol = curLocation.col;
	for (int vCol = -1; vCol <= 1; vCol++)
	{
		for (int vRow = -1; vRow <= 1; vRow++)
		{
			int newRow = curRow + vRow;
			int newCol = curCol + vCol;
			if (!world.inBounds(newRow, newCol))
				continue;

			double newDist = nodes[curRow][curCol].dist + costFn(curLocation, makeLoc(newRow, newCol), world);

			if (nodes[newRow][newCol].color == GRAY)
			{
				nodes[newRow][newCol].color = YELLOW;
				colorCell(world, makeLoc(newRow, newCol), YELLOW);
				nodes[newRow][newCol].dist = newDist;
				nodes[newRow][newCol].parent = curLocation;
				minDistQueue.enqueue(nodes[newRow][newCol].location, nodes[newRow][newCol].dist);
			}
			else
			{
				if (nodes[newRow][newCol].color == YELLOW && nodes[newRow][newCol].dist > newDist)
				{
					nodes[newRow][newCol].dist = newDist;
					nodes[newRow][newCol].parent = curLocation;
					minDistQueue.decreaseKey(nodes[newRow][newCol].location, nodes[newRow][newCol].dist);
				}
			}
		}
	}
}

Vector<Loc> getRoute(Grid<Node> &nodes, Loc start, Loc end)
{
	Vector<Loc> result;
	Loc curLoc = end;
	while (curLoc != makeLoc(-1, -1))
	{
		result.add(curLoc);
		curLoc = nodes[curLoc.row][curLoc.col].parent;
	}

	for (int i = 0; i < result.size(); i++)
	{
		if (i < result.size() - i - 1)
			swap(result[i], result[result.size() - i - 1]);
	}

	return result;
}