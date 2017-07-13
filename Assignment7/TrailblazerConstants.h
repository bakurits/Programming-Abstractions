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

/* Constant representing the caunt of neighbours for each cell */
const int KNeighbour = 8;

/* Constant stores unit distances between adjacent cells */
const Loc neighbours[] = 
{ 
    {-1, -1}, {-1, 0}, {-1, 1}, 
    {0, -1},           {0, 1},
    {1, -1}, {-1, 0}, {1, 1}
};

#endif
