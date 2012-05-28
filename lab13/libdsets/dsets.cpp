#include "dsets.h"

/*
 * addelements: 
 * 		-We add elements to the back of the vector. We assume the vector can be either empty or full.
 * params:
 *		-numelem: Number of elements you are adding to the vector.
 */

void DisjointSets::addelements(int numelem)
{

	for(int i=0; i < numelem; i++)
	{
		nodes.push_back(-1);
	}
	return;
}


/*
 * find:
 *		-Finds the parent of the given index. It compresses the path as it finds the parent.
 * params:
 *		-findnum: The node whose parent we will find.
 */

int DisjointSets::find(int findnum) 
{
	if(nodes[findnum] < 0)
	{
		return findnum;
	}
	else
	{
		return (nodes[findnum] =find(nodes[findnum]));
	}
}

/*
 * setunion:
 *		-Performs a smart union between two sets. It takes the smaller subset and points it to the bigger subset
 * params:
 *		-nodeset1, nodeset2: Indices of the vector / The two nodes that represent the set. Not necessarily the root.
 *
 */

void DisjointSets::setunion(int nodeset1, int nodeset2)
{
	int size1 = find(nodeset1);
	int size2 = find(nodeset2);

	int newSize = nodes[size1] + nodes[size2];

	if(isBigger(size1,size2))
	{
		nodes[size2] = size1;
		nodes[size1] = newSize;

	}
	else
	{
		nodes[size1] = size2;
		nodes[size2] = newSize;

	}
	
}

// HELPER FUNCTIONS

/*
 * isBigger:
 *		- Kinda lame. Initially, it was cool but useless. It just finds the bigger of the two sets.
 * params:
 * 		- size1, size2: The parent value of the two sets.
 */

bool DisjointSets::isBigger(int size1, int size2) 
{
	return size1 <= size2;
}


