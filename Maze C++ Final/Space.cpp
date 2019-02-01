#ifndef SPACECPP
#define SPACECPP

#include "Space.h"

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

//non-default constructor
Space :: Space(){
    this -> type = ' ';
    this -> row = 0;
    this -> col = 0;
    this -> visited = false;
    this -> intersection = false;
    this -> parentRow = 0;
    this -> parentCol = 0;
}

//default constructor
Space :: Space(char type, int row, int col){
    this -> type = type;
    this -> row = row;
    this -> col = col;
}

//returns the row value for a space
int Space :: getRow(){
    return this->row;
}

//returns the column value for a space
int Space :: getCol(){
    return this->col;
}

//checks if a space is visited and returns true or false
bool Space :: getVisited(){
    return this->visited;
}

//checks if a space is an intersection
bool Space :: isIntersection(){
    return intersection;
}

//sets the space to an intersection or not
void Space :: setIsIntersection(bool j){
     this -> intersection = j;
}

//sets the space to be visited or not
void Space :: setVisited(bool visited){
    this -> visited = visited;
}

//sets the space to exit type
void Space :: setExit(char character){
    this -> type = character;
}

//gets the exit type
char Space :: getExit(){
    return type;
}

//sets the row and column value for a space
void Space :: setRowAndCol(int row, int col){
    this -> row = row;
    this -> col = col;
}

//gets the type of a space
char Space :: getType(){
    return this-> type;
}

//sets the type of a space
void Space :: setType(char type){
    this -> type = type;
}

//sets the parent row and column of a space
void Space :: setParent(int row, int col){
    this->parentRow = row;
    this->parentCol = col;
}

//gets the parent row of a space
int Space :: getParentRow(){
    return this->parentRow;
}

//gets the parent column of a spaces
int Space :: getParentCol(){
    return this->parentCol;
}

#endif