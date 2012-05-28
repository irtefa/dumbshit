#ifndef __DSETS_H__
#define __DSETS_H__

//#include "easypng.h"
#include <iostream>
#include <vector>

using namespace std; 

// for detailed comments please take a look at the cpp file.
class DisjointSets{

	public:

		void addelements(int numelem); // adds elements at the end of the vector
		int find(int findnum); // returns the index of the set where the findnum resides
		void setunion(int nodeset1, int nodeset2); // the args are not necessarily the roots of the subtrees, they are a part of their set

	private:
		vector<int> nodes; // the vector which holds the parents of the nodes. The nodes are the indices of the vectors.
		bool isBigger(int size1, int size2); // helper which finds which set is bigger.
};

//
#endif