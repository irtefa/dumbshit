/**
 * @file graph_tools.h
 * This is the declaration of the tasks you will write for this lab.
 */

#ifndef _GRAPH_TOOLS_
#define _GRAPH_TOOLS_

#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_map>
#include "graph.h"
#include "libdsets/dsets.h"

using std::stack;
using std::queue;
using std::unordered_map;

using namespace std;

/**
 * This is a namespace that provides various functions for
 *  operations on the Graph class. Your assignment this lab
 *  will be to implement these three functions.
 */
namespace GraphTools
{

    /**
     * Finds the minimum edge weight in the Graph graph.
     */
     int findMinWeight(Graph & graph);

    /**
     * Returns the shortest distance (in edges) between the Vertices
     *  start and end.
     */
    int findShortestPath(Graph & graph, Vertex start, Vertex end);

    /**
     * Finds a minimal spanning tree on a graph.
     */
    void findMST(Graph & graph);

    // define any helper functions here:
	
	void findMinWeight(Graph & graph, queue<Vertex> & q, int & retval);

    void BFS(Graph & graph, Vertex start, Vertex end,queue<Vertex> & q,unordered_map<Vertex,Vertex> & p, unordered_map<Vertex,int> & distance);
}

#endif
