//
//  Space.h
//  Maze Project
//
//  Created by Aaron Bloomfield on 11/28/18.
//  CPSC 340 Section 1
//
// 

#ifndef Space_h
#define Space_h

#include <stdio.h>
#include <vector>
using namespace std;
class Space
{
public:
    //non-default constructor
    Space();
    
    //default constructor for spaces
    Space(char type, int row, int col);
    
    //returns the row for space
    int getRow();
    
    //returns the column for space
    int getCol();
    
    //returns if the space was visited
    bool getVisited();
    
    //returns if the space is an intersection
    bool isIntersection();
    
    //sets the space to an intersection
    void setIsIntersection(bool j);
    
    //sets the space to be visited
    void setVisited(bool visited);
    
    //sets the space if its an exit
    void setExit(char character);
    
    //returns the exit space
    char getExit();
    
    //sets the row and column for a space
    void setRowAndCol(int row, int col);
    
    //gets the type of space
    char getType();
    
    //sets the type of the space
    void setType(char type);
    
    //sets the parent row and column for a space
    void setParent(int row, int col);
    
    //gets the parent row
    int getParentRow();
    
    //gets the parent column
    int getParentCol();
private:
    char type;
    int row;
    int col;
    bool visited;
    bool intersection;
    int parentRow;
    int parentCol;
};

#endif /* Space_hpp */

