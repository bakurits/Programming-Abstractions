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
#include "vector.h"
using namespace std;

Vector<Loc> shortestPath(Loc start,
						 Loc end,
						 Grid<double> &world,
						 double costFn(Loc from, Loc to, Grid<double> &world),
						 double heuristic(Loc start, Loc end, Grid<double> &world))
{

	int N_Rows = world.numRows(); // Number of Rows
	int N_Cols = world.numCols(); // Number of Columns

	Grid<Node> nodes(N_Rows, N_Cols); // Stores information about grid cells.
									  // Their location, color, parent and distance from starting cell.

	TrailblazerPQueue<Loc> minDistQueue; // Stores nodes associated with their distance from sratring cell.

	prepareInitialState(world, nodes, minDistQueue, N_Rows, N_Cols, start, heuristic);

	while (!minDistQueue.isEmpty())
	{
		Loc curNode = minDistQueue.dequeueMin();
		nodes[curNode.row][curNode.col].color = GREEN;
		colorCell(world, curNode, GREEN);

		if (curNode == end)
			break;
		neighbourCheck(world, nodes, minDistQueue, curNode, end, costFn, heuristic);
	}

	if (nodes[end.row][end.col].color != GREEN)
		error("There is no route from start to end.");
	else
		return getRoute(nodes, start, end);
}

Set<Edge> createMaze(int numRows, int numCols)
{
	Grid<vector<double>> world(numRows, numCols); // Stores edge's costs
	TrailblazerPQueue<Edge> edges;				  // Stores Edges sorted by their cost
	fillWorld(world), edges;
	return getMinSpanningTree(world, edges);
}

void prepareInitialState(Grid<double> &world,
						 Grid<Node> &nodes,
						 TrailblazerPQueue<Loc> &minDistQueue,
						 int N_Rows,
						 int N_Cols,
						 Loc start,
						 double heuristic(Loc start, Loc end, Grid<double> &world))
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
	minDistQueue.enqueue(start, heuristic(start, end, world));
}

void neighbourCheck(Grid<double> &world,
					Grid<Node> &nodes,
					TrailblazerPQueue<Loc> &minDistQueue,
					Loc curLocation,
					Loc end,
					double costFn(Loc from, Loc to, Grid<double> &world),
					double heuristic(Loc start, Loc end, Grid<double> &world))
{

	int curRow = curLocation.row;
	int curCol = curLocation.col;
	for (int i = 0; i < KNeighbour; i++)
	{
		int newRow = curRow + i / 3 - 1;
		int newCol = curCol + i % 3 - 1;
		if (!world.inBounds(newRow, newCol))
			continue;

		double newDist = nodes[curRow][curCol].dist +
						 costFn(curLocation, makeLoc(newRow, newCol), world);

		if (nodes[newRow][newCol].color == GRAY)
		{
			nodes[newRow][newCol].color = YELLOW;
			colorCell(world, makeLoc(newRow, newCol), YELLOW);
			nodes[newRow][newCol].dist = newDist;
			nodes[newRow][newCol].parent = curLocation;
			minDistQueue.enqueue(nodes[newRow][newCol].location, newDist + heuristic(makeLoc(newRow, newCol), end));
		}
		else
		{
			if (nodes[newRow][newCol].color == YELLOW && nodes[newRow][newCol].dist > newDist)
			{
				nodes[newRow][newCol].dist = newDist;
				nodes[newRow][newCol].parent = curLocation;
				minDistQueue.decreaseKey(nodes[newRow][newCol].location, newDist + heuristic(makeLoc(newRow, newCol), end));
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

void fillWorld(Grid<vector<double>> &world, TrailblazerPQueue<Edge> &edges)
{
	int N_Rows = world.numRows();
	int N_Cols = world.numCols();
	for (int i = 0; i < N_Rows; i++)
	{
		for (int j = 0; j < N_Cols; j++)
		{
			for (int k = 0; k < KNeighbourForKruskal; k++)
			{
				Loc neighLoc = getNeighbour(k);
				if (world.inBounds(neighLoc.row, neighLoc.col))
				{
					if (world[neighLoc.row][neighLoc.col].size() == 0)
					{
						world[i][j].push_back(randomReal(0, 1));
						edges.enqueue(makeEdge(makeLoc(i, j), neighLoc), world[i][j][k]);
					}
					else
					{
						double edgeCost = world[neighLoc.row][neighLoc.col][getNeighbourInd(neighLoc, makeLoc(i, j))];
						world[i][j].push_back(edgeCost);
					}
				}
				else 
				{
					world[i][j].push_back(INT_MAX);
				}
			}
		}
	}
}

Set<Edge> getMinSpanningTree(Grid<vector<double>> &world, TrailblazerPQueue<Edge> &edges)
{
	Set<Edge> result; 					// Stores edges of minimum spanning tree
	Grid<int> clusterInd; 				// Stores cluster for each cell
	vector<vector<Loc>> locsInCluster;	// Stores cells for each cluster
	int clusterCount;					// Steres count of clusters
	makeclusters(clusterInd, clusterCount, locsInCluster);
	while (clusterCount > 1)
	{
		Edge E = clusterInd.dequeueMin();
		if (findCluster(E.start, clusterInd) != findCluster(E.end, clusterInd))
		{
			result.add(E);
			unionclusterInd(E.start, E.end, locsIncluster, clusterInd, clusterCount);
		}
	}
	return result;
}

double edgeCost(Loc from, Loc to, Grid<vector<double>> &world)
{
	int N_Neighbour = getNeighbourInd(from, to);
	return world[from.row][from.col][N_Neighbour];
}

int getNeighbourInd(Loc from, Loc to)
{
	int x = to.row - from.row;
	int y = to.col - from.col;

	int i = (x + y + 1) / 2;
	int j = x / (x + y);

	return i * 2 + j;
}

Loc getNeighbour(Loc from, int diff)
{
	int i = diff / 2;
	int j = diff % 2;
	int diffRow = i * (2 * j - 1);
	int diffCol = (1 - i) * (2 * j - 1);
	return makeLoc(from.row + diffRow, from.col + diffCol);
}

void makeClusters(Grid<int> &clusterInd, int &clusterCount, vector<vector<Loc>> &locsInCluster)
{
	int N_Rows = clusterInd.numRows();
	int N_Cols = clusterInd.numCols();
	clusterCount = N_Rows * N_Cols;
	for (int i = 0; i < N_Rows; i++)
	{
		for (int j = 0; j < N_Cols; j++)
		{
			int curCluster = i * N_Cols + j;
			clusterInd[i][j] = curCluster;
			vector<Loc> temp;
			temp.push_back(makeLoc(i, j));
			locsInCluster[curCluster].push_back(temp);
		}
	}
}

int findCluster(Loc curLoc, Grid<int> &clusterInd)
{
	return clusterInd[curLoc.row][curLoc.col];
}

void unionClusters(Loc first, Loc second, vector<vector<Loc>> &locsInCluster, Grid<int> &clusterInd, int &clusterCount)
{
	int firstsCluster = findCluster(first, clusterInd);
	int secondsCluster = findCluster(second, clusterInd);
	if (firstsCluster != secondsCluster)
	{
		clusterCount--;
		if (locsInCluster[firstsCluster].size() < locsInCluster[secondsCluster].size())
			swap(firstsCluster, secondsCluster);
		for (int i = 0; i < locsIncluster[secondsCluster].size())
		{
			Loc curLoc = locsIncluster[secondsCluster];
			locsIncluster[firstsCluster].push_back(curLoc);
			clusterInd[curLoc.row][curLoc.col] = firstsCluster;
		}
	}
}