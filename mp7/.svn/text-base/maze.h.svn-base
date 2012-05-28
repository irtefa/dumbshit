#ifndef __MAZE_H_
#define __MAZE_H_


#include "easypng.h"
#include <limits.h>
#include <time.h>
#include "dsets.h"
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

class SquareMaze {

	public:
		// VARIABLES	

		// solution steps
		vector<int> solution; 


		// FUNCTIONS
		
		// makemaze function
		void makeMaze(int width,int height);

		// canTravel function
		bool canTravel(int x, int y, int dir);

		// setWall
		void setWall(int x, int y, int dir, bool exists);

		// solveMaze
		void solveMaze();

		// drawMaze
		PNG * drawMaze();

		// drawMazeWithSolution
		PNG * drawMazeWithSolution();

	private:
		int size; // size of the maze


		int last_x; // stores the maximum path's x val

		struct cell
		{
			bool right;  // dir = 1
			bool bottom; // dir = 0
		};

		int w;
		int h;
		
		vector<cell> cells;
		vector<int> shuff;
	
		
		DisjointSets set;

		//HELPER


		bool validRight(int a, int b);
		bool validBottom(int a, int b);
		bool rBounds(int x, int y);
		bool bBounds(int x, int y);

		// for maze solver

		vector<bool> visited;

		bool checkVisited(int x,int y,int dir);
		int retIdx(int x,int y, int dir);

		void DFS(int x,int y,vector<int> temp);
	

};

#endif
