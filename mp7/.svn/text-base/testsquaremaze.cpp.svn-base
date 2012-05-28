/*
*  testsquaremaze.cpp
*  cs225 Maze MP
*  Performs basic tests of SquareMaze.
*  Written April 2007 by Jonathan Ray
*/

#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "easypng.h"

int main()
{ 
   SquareMaze m;
   m.makeMaze(50,50);
   std::cout << "MakeMaze complete" << std::endl;

   PNG* unsolved = m.drawMaze();
   unsolved->writeToFile("unsolved.png");
   delete unsolved;
   std::cout << "drawMaze complete" << std::endl;
   
   m.solveMaze();
   std::cout << "solveMaze complete" << std::endl;
   
   
   PNG* solved = m.drawMazeWithSolution();
   solved->writeToFile("solved.png");
   delete solved;
   std::cout << "drawMazeWithSolution complete" << std::endl;
   
   return 0;
}

