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
Vector<Loc>
shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world));

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
void prepareInitialState(Grid<double>& world, 
						 Grid<Node> &nodesCondition, 
						 TrailblazerPQueue<Loc> &minDistQueue, 
						 int N_Rows, 
						 int N_Cols, 
						 Loc start);

/* Function: neighbourCheck
 *
 * This method checks each neighbour of current node.
 * Changes color and current distance from starting node if it's necessary.
 */
void neighbourCheck(Grid<double>& world, 
					Grid<Node> &nodesCondition, 
					TrailblazerPQueue<Loc> &minDistQueue, 
					Loc curLocation,
					double costFn(Loc from, Loc to, Grid<double>& world));

/* Function: getRoute
 *
 * This function returns best route from start to end.
 */
Vector <Loc> getRoute(Grid<Node> &nodesCondition, Loc start, Loc end);

#endif
