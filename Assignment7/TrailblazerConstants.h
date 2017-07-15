/******************************************************************************
 * File: TrailblazerConstants.h
 *
 * Constants useful for the Trailblazer program.
 */

#ifndef TrailblazerConstants_Included
#define TrailblazerConstants_Included

/* Constant representing the value of a wall cell in a maze. */
const double kMazeWall = 0.0;

/* Constant representing the value of a floor cell in a maze. */
const double kMazeFloor = 1.0;

/* Constant representing the caunt of neighbours for each cell for Djikstra*/
const int KNeighbourForDjikstra = 9;

/* Constant representing the caunt of neighbours for each cell for Kruskal */
const int KNeighbourForKruskal = 4;

#endif
