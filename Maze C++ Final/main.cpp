//
//  main.cpp
//  Maze Project
//
//  Created by Aaron Bloomfield on 11/28/18.
//  CPSC 340 Section 1
//
// This code is the creation of a project that takes in data from a text file, converts it into a maze, and then creates a solution to the maze using stacks or queues.

#include <fstream>
#include <iostream>
using namespace std;
#include "Maze.h"
#include "Space.h"

int main ( int argc, char *argv[] )
{
  //creates initial space
  Space temp(' ', 1, 0);
  
  Maze maze(argv[1], 1, 0);
  Maze maze1(argv[1], 1, 0);
  maze.printMaze();
  cout << "Using Hermione’s Path Magic Spell" << endl;
  cout << "------------------------------------------------" << endl;
  maze.findExitStack(temp);
  
  cout << endl;
  cout << "Using Ron’s Path Magic Spell" << endl;
  cout << "------------------------------------------------" << endl;
  maze1.findExitQueue(temp);
  
  
  return 0;
}