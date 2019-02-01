//
//  maze.h
//  Maze Project
//
//  Created by Aaron Bloomfield on 11/28/18.
//  CPSC 340 Section 1
//

#ifndef Maze_h
#define Maze_h

#include <vector>
#include <string>
#include <stack>
#include <queue>
#include "Space.h"
using namespace std;
class Maze
{
	public:
	    //non-default constructor
		Maze();
		
		//default constructor
		Maze(string filename, int initialR, int initialC);
		
		//sets initial row and column
		bool setInitial(int r, int c);
		
		//returns the row and column for a space
		Space getSpace(int r, int c);
		
		//checks for all neighbors of the space in the stack
		stack<Space> getFreeNeighborsStack(Space currentSpace);
		
		//solution to find the path and exit of the maze for stack
		bool findExitStack(Space currentSpace);
		
		//return the solution stack
		stack<Space> getSolutionStack();
		
		//checks all neighbors of the space in the queue
		queue<Space> getFreeNeighborsQueue(Space currentSpace);
		
		//slution to find the path and exit of the maze for queue
		bool findExitQueue(Space currentSpace);
		
		//returns the solution for the queue
		queue<Space> getSolutionQueue();
		
		//prints maze
		void printMaze();

	private:
		void print();
		Space grid[100][100];
		int rows, cols; //how many rows and columns is the maze you read in
		int sRow, sCol; //Start Row and Start Column
		int currentR, currentC;
		stack <Space> freeNeighborsStack;
		stack <Space> solutionStack;
		queue <Space> freeNeighborsQueue;
		queue <Space> solutionQueue;
};
#endif /* Maze_h */
