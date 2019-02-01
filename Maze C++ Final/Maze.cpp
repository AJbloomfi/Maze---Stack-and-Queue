//
//  maze.cpp
//  Maze Project
//
//  Created by Aaron Bloomfield on 11/28/18.
//  CPSC 340 Section 1
//

#ifndef MAZECPP
#define MAZECPP

#include "Maze.h"

#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <fstream>
#include <iostream>
#include "Space.h"
using namespace std;

//non-default constructor
Maze :: Maze(){
    	this -> grid[100][100];
		this -> rows = 0;
		this -> cols = 0;
		this -> sRow = 0;
		this -> sCol = 0;
		this -> currentR = 0;
		this -> currentC = 0;
		stack <Space> freeNeighborsStack;
		stack <Space> solutionStack;
		queue <Space> freeNeighborsQueue;
		queue <Space> solutionQueue;
}


//default constructor that inputs and parses a file
Maze :: Maze(string filename, int initialR, int initialC){
    string line;
	ifstream input(filename);
	getline(input, line);
	
	//gets the size of the maze
	rows = stoi(line.substr(0, line.find(" ")));
	line.erase(line.begin(), line.begin()+2);
	cols = stoi(line);
	
	//sets grid size
	grid[rows][cols];
	
	//makes a blank grid
	for(int x=0; x<rows; x++){
	    for(int i=0; i<cols; i++){
	        Space temp(' ', x, i);
	        grid[x][i] = temp;
	    }
	}
	grid[initialR][initialC].setType('E');
	
	int row;
	int col;
	
	//gets input and places the walls
	while(input.good()){
		getline(input, line);
		
		row = stoi(line.substr(0, line.find(" ")));
	    line.erase(line.begin(), line.begin()+2);
	    col = stoi(line);
	    Space temp('*',row, col);
	    grid[row][col] = temp;
	}
	
	//places the exit
	for(int x=0; x<rows; x++){
	    if(grid[x][cols-1].getType() == ' '){
	        grid[x][cols-1].setType('X');
	    }

	}
}

//sets initial row and column
bool Maze :: setInitial(int r, int c){
    grid[r][c].setType('E');
}

//returns the row and column space
Space Maze:: getSpace(int r, int c){
    return grid[r][c];
}

//checks neighbors of the space
stack<Space> Maze :: getFreeNeighborsStack(Space currentSpace){
    
    //makes sure that the stack is empty, clears it
    while(freeNeighborsStack.size()>0){
        freeNeighborsStack.pop();
    }
    int row = currentSpace.getRow();
    int col = currentSpace.getCol();
    
    //checks for out of bounds for east
    if(col+1<cols){
        //checks for a wall and visited
        if(grid[row][col+1].getType() != '*'&& grid[row][col+1].getVisited() == false){
             freeNeighborsStack.push(grid[row][col+1]);
        
        } 
    }
    //checks out of bounds
    if(col-1>=0){
        if(grid[row][col-1].getType() != '*'&& grid[row][col-1].getVisited() == false){
            freeNeighborsStack.push(grid[row][col-1]);
        
        }
    }
    //checks out of bounds
    if(row+1<this->rows){
        if(grid[row+1][col].getType() != '*'&& grid[row+1][col].getVisited() == false){
             freeNeighborsStack.push(grid[row+1][col]);
        }
    }
    //checks out of bounds
    if(row-1>=0){
        if(grid[row-1][col].getType() != '*'&& grid[row-1][col].getVisited() == false){
            freeNeighborsStack.push(grid[row-1][col]);
        
        }
    }
    return freeNeighborsStack;
    
}

bool Maze :: findExitStack(Space currentSpace){
    
    //sets current space to the current grid space
    currentSpace = grid[currentSpace.getRow()][currentSpace.getCol()];
    while(1){
        //checks if the current space is not visited
        if(currentSpace.getVisited() != true){
            //sets it to visited
            currentSpace.setVisited(true);
            
            //sets the grid space to visited 
            grid[currentSpace.getRow()][currentSpace.getCol()].setVisited(true);
            
            //pushes current space to the solution stack
            solutionStack.push(currentSpace);
            
            //sets each move on the path to a P and prints the maze with each update
            if(grid[currentSpace.getRow()][currentSpace.getCol()].getType() != 'X'){
                grid[currentSpace.getRow()][currentSpace.getCol()].setType('P');
                printMaze();
                
            }
            //checks to see if the exit was found
            if(grid[currentSpace.getRow()][currentSpace.getCol()].getType() == 'X'){
                
                cout << "Hermione’s Solution" << endl;
                cout << "------------------------------------------------";
                
            }
            
            cout << endl;
        }
        //checks to see if the exit was found
        if(grid[currentSpace.getRow()][currentSpace.getCol()].getType() == 'X'){
            
            printMaze();
            return true;
        }
        
        stack <Space> freeNeighborsStack = getFreeNeighborsStack(currentSpace);
        
        //checks the stack to see if theres more than 1 neighbor, becomes an intersection
        if(freeNeighborsStack.size() > 1){
            currentSpace.setIsIntersection(true);
            grid[currentSpace.getRow()][currentSpace.getCol()].setIsIntersection(true);
        }
        
        //checks if there is no neighbor, causing it to backtrack
        else if(freeNeighborsStack.size() == 0){
            
            //backtracks
            while(!solutionStack.empty() && grid[currentSpace.getRow()][currentSpace.getCol()].isIntersection() == false){
                currentSpace = solutionStack.top();
                solutionStack.pop();
            }
            if(solutionStack.size() == 0){
                return false;
            }
            else{
                solutionStack.push(currentSpace);
                grid[currentSpace.getRow()][currentSpace.getCol()].setIsIntersection(false);
                currentSpace.setIsIntersection(false);
            }
        }
        
        if(freeNeighborsStack.size() >= 1){
            currentSpace = freeNeighborsStack.top();
            currentSpace = grid[currentSpace.getRow()][currentSpace.getCol()];

        }
        
        
    }
    return false;
    
}

//returns solution stack
stack<Space> Maze :: getSolutionStack(){
    return solutionStack;
}

//checks neighbor of the space for queue
queue<Space> Maze :: getFreeNeighborsQueue(Space currentSpace){
    
    //makes sure neighbor queue is empty
    while(freeNeighborsQueue.size()>0){
        freeNeighborsQueue.pop();
    }
    int row = currentSpace.getRow();
    int col = currentSpace.getCol();
    
    //checks out of bounds for east
    if(col+1<this->cols){
        if(grid[row][col+1].getType() != '*'&& grid[row][col+1].getVisited() == false){
            freeNeighborsQueue.push(grid[row][col+1]);
        
        } 
    }
    //checks out of bounds for west
    if(col-1>=0){
        if(grid[row][col-1].getType() != '*'&& grid[row][col-1].getVisited() == false){
            freeNeighborsQueue.push(grid[row][col-1]);
        
        }
    }
    //checks out of bounds for south
    if(row+1<this->rows){
        if(grid[row+1][col].getType() != '*'&& grid[row+1][col].getVisited() == false){
            freeNeighborsQueue.push(grid[row+1][col]);
        }
    }
    
    //checks out of bounds for north
    if(row-1>=0){
        if(grid[row-1][col].getType() != '*'&& grid[row-1][col].getVisited() == false){
            freeNeighborsQueue.push(grid[row-1][col]);
        
        }
    }
    return freeNeighborsQueue;
    

    
}

bool Maze :: findExitQueue(Space currentSpace){
    //bool flag = false;
    
    //sets current space to the current grid space
    currentSpace = grid[currentSpace.getRow()][currentSpace.getCol()];
    
    //sets the parents of the grid to -1, -1
    grid[currentSpace.getRow()][currentSpace.getCol()].setParent(-1,-1);
    
    while(1){
        //checks if current space is visited
        if(currentSpace.getVisited() != true){
            
            //sets the grid space to visited
            grid[currentSpace.getRow()][currentSpace.getCol()].setVisited(true);
            
            //pushes the current space to solution queue since its not visited
            solutionQueue.push(currentSpace);
            
            //sets the currrent grid space to p for the path
            if(grid[currentSpace.getRow()][currentSpace.getCol()].getType() != 'X'){
                grid[currentSpace.getRow()][currentSpace.getCol()].setType('P');
                printMaze();
            }
            
            //checks to see if it reaches the exit
            if(grid[currentSpace.getRow()][currentSpace.getCol()].getType() == 'X'){
                cout << "Ron’s Solution" << endl;
                cout << "------------------------------------------------" << endl;
                printMaze();
            }
            //printMaze();
            cout << endl;
        }
        
        //checks to see if the exit was found
        if(currentSpace.getType() == 'X'){
            return true;
        }
        
        freeNeighborsQueue = getFreeNeighborsQueue(currentSpace);
        
        //checks to make sure there is something in the freenieghbors queue
        if(freeNeighborsQueue.size() !=  0){
            
            currentSpace = freeNeighborsQueue.front();
            currentSpace = grid[currentSpace.getRow()][currentSpace.getCol()];
        }
        else{
            return false;
        }
        
        
    }
    
}

//returns the solution queue
queue<Space> Maze :: getSolutionQueue(){
    return solutionQueue;
}

//prints out the maze
void Maze :: printMaze(){
    
    
    
    for(int x=0; x<rows; x++){
        
	    
	    for(int i=0; i<cols; i++){
	        
	        cout << grid[x][i].getType();
	        
	    }
	    
	    cout << endl;
	}
    
}
#endif