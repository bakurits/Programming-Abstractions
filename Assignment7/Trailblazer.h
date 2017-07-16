/******************************************************************************
 * File: Trailblazer.h
 *
 * Exports functions that use Dijkstra's algorithm, A* search, and Kruskal's
 * algorithm as specified in the assignment handout.
 */

#ifndef Trailblazer_Included
#define Trailblazer_Included

#include "TrailblazerTypes.h"
#include "set.h"
#include "grid.h"
#include "TrailblazerPQueue.h"
#include "vector.h"

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
 * search.  Make sure to update both this function prototype and the
 * implementation inside of Trailblazer.cpp.
 */
Vector<Loc> shortestPath(Loc start, Loc end,
						 Grid<double> &world,
						 double costFn(Loc from, Loc to, Grid<double> &world),
						 double heuristic(Loc start, Loc end, Grid<double> &world));

/* Function: createMaze
 * 
 * Creates a maze of the specified dimensions using a randomized version of
 * Kruskal's algorithm, then returns a set of all of the edges in the maze.
 *
 * As specified in the assignment handout, the edges you should return here
 * represent the connections between locations in the graph that are passable.
 * Our provided starter code will then use these edges to build up a Grid
 * representation of the maze.
 */
Set<Edge> createMaze(int numRows, int numCols);

/* Function: prepareInitialState
 *
 * This function prepares initial state of algorithm
 * Makes nodes grey and Puts srarting point in queue.
 */
void prepareInitialState(Grid<double> &world, Grid<Node> &nodes,
						 TrailblazerPQueue<Loc> &minDistQueue,
						 int N_Rows, int N_Cols,
						 Loc start, Loc end,
						 double heuristic(Loc start, Loc end, Grid<double> &world));

/* Function: neighbourCheck
 *
 * This method checks each neighbour of current node.
 * Changes color and current distance from starting node if it's necessary.
 */
void neighbourCheck(Grid<double> &world,
					Grid<Node> &nodes,
					TrailblazerPQueue<Loc> &minDistQueue,
					Loc curLocation,
					Loc end,
					double costFn(Loc from, Loc to, Grid<double> &world),
					double heuristic(Loc start, Loc end, Grid<double>& world));

/* Function: getRoute
 *
 * This function returns best route from start to end.
 */
Vector<Loc> getRoute(Grid<Node> &nodes, Loc start, Loc end);

/* Function: fillWorld
 *
 * This function fills world with random costs
 * For edges between adjacent cells
 */
void fillWorld(Grid<Vector<double>> &world, TrailblazerPQueue<Edge> &edges);

/* Function: getMinSparingTree
 *
 * This function returs minimum spanning tree
 */
Set <Edge> getMinSpanningTree(Grid<Vector<double>> &world, TrailblazerPQueue<Edge> &edges);

/* Function: EdgeCost
 *
 * This function returns cost of edge
 * Between "from" and "to"
 */
double edgeCost(Loc from, Loc to, Grid<Vector<double>> &world);

/* Function : getNeighbourInd
 *
 * This function return index of "to" in "from's" neighbour list.
 * You can find more information about this function in README.docx.
 */
int getNeighbourInd(Loc from, Loc to);

/* Function : getNeighbour
 *
 * This function returns "diff"-th meighbour of "from"
 * You can find more information about this function in README.docx.
 */
Loc getNeighbour(Loc from, int diff);

/* Function: makeClusters
 *
 * This function makes initial state for clusters
 */
void makeClusters(Grid <int> &clusters, int &clusterCount);

/* Function: findCluster
 *
 * This method finds cluster where "curLoc" is located
 */
int findCluster(Loc curLoc, Grid <int> &clusters);

/* Function: unionClusters
 *
 * This function unions two cluster
 * You can find more information about this function in README.docx.
 */
void unionClusters(Loc first, Loc second, Grid <int> &clusters, int &clusterCount);

#endif
