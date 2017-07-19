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
#include "TrailblazerConstants.h"
#include "random.h"

using namespace std;

Vector<Loc> shortestPath(Loc start, Loc end,
						 Grid<double> &world,
						 double costFn(Loc from, Loc to, Grid<double> &world),
						 double heuristic(Loc start, Loc end, Grid<double> &world))
{

	int N_Rows = world.nRows; // Number of Rows
	int N_Cols = world.numCols; // Number of Columns

	Grid<Node> nodes(N_Rows, N_Cols); // Stores information about grid cells.
									  // Their location, color, parent and distance from starting cell.

	TrailblazerPQueue<Loc> minDistQueue; // Stores nodes associated with their distance from sratring cell.

	prepareInitialState(world, nodes, minDistQueue, N_Rows, N_Cols, start, end, heuristic);

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
	Grid<Vector<double>> world(numRows, numCols);	// Stores edge's costs
	TrailblazerPQueue<Edge> edges;	// Stores Edges sorted by their cost
	fillWorld(world, edges);
	return getMinSpanningTree(world, edges);
}

void prepareInitialState(Grid<double> &world, Grid<Node> &nodes,
						TrailblazerPQueue<Loc> &minDistQueue,
						int N_Rows, int N_Cols,
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

void neighbourCheck(Grid<double> &world, Grid<Node> &nodes,
					TrailblazerPQueue<Loc> &minDistQueue,
					Loc curLocation, Loc end,
					double costFn(Loc from, Loc to, Grid<double> &world),
					double heuristic(Loc start, Loc end, Grid<double> &world))
{

	int curRow = curLocation.row;
	int curCol = curLocation.col;
	for (int i = 0; i < KNeighbourForDjikstra; i++)
	{
		int newRow = curRow + i / 3 - 1;
		int newCol = curCol + i % 3 - 1;
		if (!world.inBounds(newRow, newCol))
			continue;

		double newDist = nodes[curRow][curCol].dist +
						 costFn(curLocation, makeLoc(newRow, newCol), world);
		double newDistWithHeuristic = newDist + heuristic(makeLoc(newRow, newCol), end, world);

		if (nodes[newRow][newCol].color == GRAY)
		{
			nodes[newRow][newCol].color = YELLOW;
			colorCell(world, makeLoc(newRow, newCol), YELLOW);
			nodes[newRow][newCol].dist = newDist;
			nodes[newRow][newCol].parent = curLocation;
			minDistQueue.enqueue(nodes[newRow][newCol].location, newDistWithHeuristic);
		}
		else
		{
			if (nodes[newRow][newCol].color == YELLOW && nodes[newRow][newCol].dist > newDist)
			{
				nodes[newRow][newCol].dist = newDist;
				nodes[newRow][newCol].parent = curLocation;
				minDistQueue.decreaseKey(nodes[newRow][newCol].location, newDistWithHeuristic);
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

void fillWorld(Grid<Vector<double>> &world, TrailblazerPQueue<Edge> &edges)
{
	int N_Rows = world.nRows;
	int N_Cols = world.nCols;
	for (int i = 0; i < N_Rows; i++)
	{
		for (int j = 0; j < N_Cols; j++)
		{
			Loc curLoc = makeLoc(i, j);
			for (int k = 0; k < KNeighbourForKruskal; k++)
			{
				Loc neighLoc = getNeighbour(curLoc, k);
				world[i][j].add(INT_MAX);
				if (!world.inBounds(neighLoc.row, neighLoc.col))
					continue;
				if (world[neighLoc.row][neighLoc.col].size() == 0)
				{
					world[i][j][k] = randomReal(0, 1);
					edges.enqueue(makeEdge(curLoc, neighLoc), world[i][j][k]);
				}
				else
				{
					double edgeCost = world[neighLoc.row][neighLoc.col][getNeighbourInd(neighLoc, curLoc)];
					world[i][j][k] = edgeCost;
				}
			}
		}
	}
}

Set<Edge> getMinSpanningTree(Grid<Vector<double>> &world, TrailblazerPQueue<Edge> &edges)
{
	Set<Edge> result;	// Stores edges of minimum spanning tree
	Grid<Loc> cluster(world.nRows, world.nCols);	// Stores root of current cluster
	makeClusters(cluster);
	while (!edges.isEmpty())
	{
		Edge E = edges.dequeueMin();
		if (findCluster(E.start, cluster) != findCluster(E.end, cluster))
		{
			result.add(E);
			unionClusters(E.start, E.end, cluster);
		}
	}
	return result;
}

double edgeCost(Loc from, Loc to, Grid<Vector<double>> &world)
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

void makeClusters(Grid<Loc> &cluster)
{
	int N_Rows = cluster.nRows;
	int N_Cols = cluster.nCols;
	for (int i = 0; i < N_Rows; i++)
	{
		for (int j = 0; j < N_Cols; j++)
		{
			cluster[i][j] = makeLoc(i, j);
		}
	}
}

Loc findCluster(Loc curLoc, Grid<Loc> &cluster)
{
	if (cluster[curLoc.row][curLoc.col] == curLoc) 
		return curLoc;
	return cluster[curLoc.row][curLoc.col] = 
			findCluster(cluster[curLoc.row][curLoc.col], cluster);
}

void unionClusters(Loc first, Loc second,
				   Grid<Loc> &cluster)
{
	Loc firstsCluster = findCluster(first, cluster);
	Loc secondsCluster = findCluster(second, cluster);
	if (firstsCluster != secondsCluster)
	{
		cluster[firstsCluster.row][firstsCluster.col] = second;
	}
}