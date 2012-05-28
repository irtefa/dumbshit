#include "maze.h"

/*
 * The Maze constructor.
 *	
 * Each individual cell is represented by a struct.
 * The cells are stored in the cells vector.
 *
 */ 

void SquareMaze::makeMaze(int width, int height)
{
	
	w = width;
	h = height;
	size = width * height;
	set.addelements(width * height);
	srand ( time(NULL) );

	cells.clear();
	shuff.clear();
	solution.clear();

	for(int i = 0; i < size;i++)
	{
		cell a;
		cells.push_back(a);
		cells[i].right  = true;
		cells[i].bottom = true;
		shuff.push_back(i);
	}

	random_shuffle(shuff.begin(),shuff.end());

	for(int i = 0; i < shuff.size();i++)
	{
		int x = shuff[i]%w;
		int y = (i - x)/w;
		
		if(rBounds(x,y))
		{
			if(validRight(x,y))
			{
				setWall(x,y,1,false);//setwal
				set.setunion((x + (y*w)),((x+1)+(y*w)));
			}
		}
	}

	random_shuffle(shuff.begin(),shuff.end());

	for(int i = 0; i < shuff.size();i++)
	{
		int x = shuff[i]%w;
		int y = (i - x)/w;

		if(bBounds(x,y))
		{
			if(validBottom(x,y)){	
				setWall(x,y,0,false);//setwall
				set.setunion((x + (y*w)),(x+((y+1)*w)));
			}
		}
	}

		random_shuffle(shuff.begin(),shuff.end());

	for(int i = 0; i < shuff.size();i++)
	{
		int x = shuff[i]%w;
		int y = (i - x)/w;
		
		if(rBounds(x,y))
		{
			if(validRight(x,y))
			{
				setWall(x,y,1,false);//setwall
				set.setunion((x + (y*w)),((x+1)+(y*w)));
			}
		}
	}

	random_shuffle(shuff.begin(),shuff.end());

	for(int i = 0; i < shuff.size();i++)
	{
		int x = shuff[i]%w;
		int y = (i - x)/w;

		if(bBounds(x,y))
		{
			if(validBottom(x,y))
			{	
				setWall(x,y,0,false);//setwall
				set.setunion((x + (y*w)),(x+((y+1)*w)));
			}
		}
	}
	
}

// Checks if you can travel. You cannot travel if you are out of bounds or you are blocked by a wall.

bool SquareMaze::canTravel(int x, int y, int dir)
{
	if(dir==0)//right
	{
	
		int idx = x + (y*w);
		if(idx < 0) return false;
		if(x >= w-1) return false;
		if(cells[idx].right) return false;
		return true;
	}
	else if(dir==1)//bottom
	{
		int idx = x + (y*w);
		if(idx < 0) return false;
		if(y >= h-1) return false;
		if(cells[idx].bottom) return false;
		return true;
	}
	else if(dir==2)//left
	{
		int idx = x-1 + (y*w);
		if(idx < 0) return false;
		if(x <= 0) return false;
		if(cells[idx].right) return false;
		return true;
	}
	else if(dir==3)//up
	{
		int idx = x + ((y-1)*w);
		if(idx < 0) return false;
		if(y<=0) return false;
		if(cells[idx].bottom) return false;
		return true;
	}
	else //if the dir is incorrect
		return false;
}

/*
 *	Setwall.
 *	Initially I set everything to wall.
 *  So, I use the setwall function to remove walls.
 */

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{	
	if(dir > 1 || dir < 0)
		return;

	int i = x + (y * w);// calc with x and y

	// if its the very last cell or not within the cell
	if(i > size - 1 || i < 0)
	{
		return;
	}

	// setting the bottom wall
	if(dir==0)
	{
		int j = x + ((y+1) * w);

		cells[i].bottom = exists;
		//set.setunion(i,j);

	}
	// setting the right wall
	else
	{
		int j = x + 1 + (y*w);

		cells[i].right  = exists;
		//set.setunion(i,j);

	}
}


// Helper to check if the cell has been already visited

bool SquareMaze::checkVisited(int x,int y,int dir)
{
	if(dir==0)//right
	{
		int idx = x+1 + (y*w);
		return visited[idx];
	}
	else if(dir==1)//bottom
	{
		int idx = x + ((y+1)*w);
		return visited[idx];
	}
	else if(dir==2)//left
	{
		int idx = x-1 + (y*w);
		return visited[idx];
	}
	else if(dir==3)//up
	{
		int idx = x + ((y-1)*w);
		return visited[idx];
	}
	else //if the dir is incorrect
		return true;
}

// Helper to return the future index by using x,y and the future direction.

int SquareMaze::retIdx(int x,int y, int dir)
{
	if(dir==0)//right
	{
		int idx = x + (y*w);
		return idx;
	}
	else if(dir==1)//bottom
	{
		int idx = x + (y*w);
		return idx;
	}
	else if(dir==2)//left
	{
		int idx = x-1 + (y*w);
		return idx;
	}
	else //if(dir==3)//up
	{
		int idx = x + ((y-1)*w);
		return idx;
	}
	//else;
}

// DrawMaze

PNG * SquareMaze::drawMaze()
{
	PNG * retval = new PNG(w*10+1,h*10+1);

	// blacken top most row

	for(int i = 0; i < w*10+1;i++)
		for(int j = 0; j < h*10+1;j++)
	{
		if(i > 9 && j==0)
		{
			(*retval)(i,j)->red   = 0;
			(*retval)(i,j)->green = 0;
			(*retval)(i,j)->blue  = 0;
		}
		else if(i==0)
		{
			(*retval)(i,j)->red = 0;
			(*retval)(i,j)->green = 0;
			(*retval)(i,j)->blue = 0;
		}
		else;
	}


	for(int i = 0; i < w;i++)
		for(int j = 0; j < h;j++)	
	{
			int ind = i + (j*w);
			if(cells[ind].bottom)
			{
				for(int k = 0; k < 10;k++)
				{
					(*retval)(i*10+k, (j+1)*10)->red = 0;
					(*retval)(i*10+k, (j+1)*10)->green = 0;
					(*retval)(i*10+k, (j+1)*10)->blue = 0;

				}
			}
			if(cells[ind].right)
			{
				for(int k=0;k < 10;k++)
				{
					 (*retval)((i+1)*10,j*10+k)->red = 0;
					 (*retval)((i+1)*10,j*10+k)->green = 0;
					 (*retval)((i+1)*10,j*10+k)->blue = 0;
				}
			}
		
	}

	return retval;
}

// DrawMazeWithSolution
PNG * SquareMaze::drawMazeWithSolution()
{
	PNG * var = drawMaze();

	int x = 5;
	int y = 5;



	for(int a = 0; a < solution.size();a++)
	{

		if(solution[a]==0)//right
		{
			for(int i=0;i < 10;i++)
			{
				(*var)((x+i),y)->red = 255;
				(*var)((x+i),y)->green = 0;
				(*var)((x+i),y)->blue = 0;
			}
			x += 10;
		}
		else if(solution[a]==3)//up
		{
			for(int i=0;i < 10;i++)
			{
				(*var)(x,(y-i))->green = 0;
				(*var)(x,(y-i))->red = 255;
				(*var)(x,(y-i))->blue = 0;
			}
			y -= 10;
		}
		else if(solution[a]==2)//left
		{
			for(int i=0; i< 10;i++)
			{
				(*var)((x-i),y)->green = 0;
				(*var)((x-i),y)->blue = 0;
				(*var)((x-i),y)->red = 255;
			}
			x -= 10;	
		}
		else
		{
			for(int i=0; i < 10;i++)
			{
				(*var)(x,(y+i))->green = 0;
				(*var)(x,(y+i))->blue = 0;
				(*var)(x,(y+i))->red = 255;
			}
			y+=10;
		}
	}

	x = last_x;
	y = h -1;

	for(int k=0;k <= 9;k++)
	{
		(*var)(x * 10 + k, (y+1) * 10)->red   = 255;
		(*var)(x * 10 + k, (y+1) * 10)->green = 255;
		(*var)(x * 10 + k, (y+1) * 10)->blue  = 255;
	}

	return var;
}

// Checks if you can go right. Only returns false if you are going out of bounds from right

bool SquareMaze::rBounds(int x, int y)
{
	if(y>=h-1 && x>=w-1) return false;
	
	if(x>=w-1)
		return false;
	else
		return true;
}

// Checks if you can go to the bottom. Only returns false if you are going out of bounds at the bottom

bool SquareMaze::bBounds(int x, int y)
{
	if(y>=h-1 && x>=w-1) return false;
	
	if(y>=h-1)
		return false;
	return true;
}

// Checks validity of moving right using the disjointsets

bool SquareMaze::validRight(int x, int y)
{
	if(x >= w-1)
	{
		return false;
	}

	int curr = x + (y * w);
	int right = x + 1 + (y * w);

	
	if(set.find(curr) == set.find(right))
	{
		return false;
	}

	return true;
}

// Checks the validity of going to the bottom using the disjointsets

bool SquareMaze::validBottom(int x, int y)
{
	
	if(y >= h-1)
	{
		return false;
	}

	int curr = x + (y*w);
	int bottom = x + ( (y + 1 ) * w);

	
	if(set.find(curr)==set.find(bottom))
	{
		return false;
	}

	return true;
}

// Solves the Maze by a Depth First Search function

void SquareMaze::solveMaze()
{
	visited.clear();


	for(int i=0;i < size;i++)
		visited.push_back(false);

	vector<int> temp;
	last_x = INT_MAX;
	
	DFS(0,0,temp);
}

// The Depth First Search function that solves the Maze

void SquareMaze::DFS(int x,int y,vector<int> temp)
{
	if(y==h-1)
	{
		if(temp.size() > solution.size())
		{
			solution = temp;
			last_x = x;
		}
		// when both paths are of equal length
		else if(temp.size() == solution.size())
		{
			if(x < last_x)
			{
				last_x = x;
				solution = temp;
			}
		}
	}

	// Move Right

	if(canTravel(x,y,0) && !checkVisited(x,y,0))
	{
		temp.push_back(0);
		visited[retIdx(x,y,0)] = true;
		DFS(x+1,y,temp);
		temp.pop_back();
		
	}

	// Move Down

	if(canTravel(x,y,1) && !checkVisited(x,y,1))
	{
		temp.push_back(1);
		visited[retIdx(x,y,1)] = true;
		DFS(x,y+1,temp);
		temp.pop_back();
		
	}

	// Move Left

	if(canTravel(x,y,2) && !checkVisited(x,y,2))
	{
		temp.push_back(2);
		visited[retIdx(x,y,2)] = true;
		DFS(x-1,y,temp);
		temp.pop_back();
	}

	// Move Up

	if(canTravel(x,y,3) && !checkVisited(x,y,3))
	{
		temp.push_back(3);
		visited[retIdx(x,y,3)] = true;
		DFS(x,y-1,temp);
		temp.pop_back();
	}
}