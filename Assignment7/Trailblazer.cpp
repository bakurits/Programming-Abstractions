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
	Grid<Vector<double>> world(numRows, numCols); // Stores edge's costs
	TrailblazerPQueue<Edge> edges;				  // Stores Edges sorted by their cost
	fillWorld(world), edges;
	return getMinSpanningTree(world);
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
		int newRow = curRow + neighbours[i].row;
		int newCol = curCol + neighbours[i].col;
		if (!world.inBounds(newRow, newCol))
			continue;

		double newDist = nodes[curRow][curCol].dist +
						 costFn(curLocation, makeLoc(newRow, newCol), world) +
						 heuristic(makeLoc(newRow, newCol), end);

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
	int N_Rows = world.numRows();
	int N_Cols = world.numCols();
	for (int i = 0; i < N_Rows; i++)
	{
		for (int j = 0; j < N_Cols; j++)
		{
			for (int k = 0; k < KNeighbour; k++)
			{
				neighRow = i + neighbours[k].row;
				neighCol = j + neighbours[k].col;
				world[i][j].add(randomReal(0, 1) * world.inBounds(neighRow, neighCol));
				edges.enqueue(makeEdge(makeLo1c(i, j), makeLoc(neighRow, neighCol)), world[i][j][k]);
			}
		}
	}
}

Set<Edge> getMinSpanningTree(Grid<Vector<double>> &world, TrailblazerPQueue<Edge> &edges)
{
	Set<Edge> result;
	Grid <Loc> clusters;
	int clusterCount;
	makeClusters(clusters, clusterCount);
	while (clusterCount > 1)
	{
		Edge E = clusters.dequeueMin();
		if (findCluster(E.start, clusters) != findCluster(E.end, clusters))
		{
			result.add(E);
			unionClusters(E.start, E.end, clusters, clusterCount);
		}
	}
	return result;
}

double edgeCost(Loc from, Loc to, Grid<Vector<double>> &world)
{
	int rowDif = to.row - from.row;
	int ColDif = to.col - from.col;
	int N_Neighbour = rowDif * 3 + ColDif;

	if (N_Neighbour > 4)
		N_Neighbour--;

	return world[from.row][from.col][N_Neighbour];
}