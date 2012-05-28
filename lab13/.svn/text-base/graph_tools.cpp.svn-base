/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	vector<Edge> edges = graph.getEdges();
	vector<Vertex> v   = graph.getVertices();

	for(unsigned int i = 0; i < v.size(); i++)
	{
		graph.setVertexLabel(v[i],"");
	}
	for(unsigned int i = 0; i < edges.size(); i++)
	{
		graph.setEdgeLabel(edges[i].source,edges[i].dest,"UNEXPLORED");
	}

	queue<Vertex> q;

	unordered_map<Vertex,Vertex> p;

   	unordered_map<Vertex,int> distance;

	BFS(graph,start,end,q,p,distance);

	Vertex temp = end;
	Vertex parent = p[end];

	while(parent!= start)
	{
		graph.setEdgeLabel(temp,parent,"MINPATH");
		temp = parent;
		parent = p[temp];
	}
	
	return distance[end];
}

void GraphTools::BFS(Graph & graph, Vertex start, Vertex end,queue<Vertex> & q,unordered_map<Vertex,Vertex> & p,unordered_map<Vertex,int> & distance)
{

   	Vertex var = start;  	
	q.push(var);

	graph.setVertexLabel(var,"VISITED");
	graph.getVertexLabel(var);
	p[start] = start;
	distance[var] = 0;

	while(!q.empty())
	{
	
		var = q.front();
		q.pop();

		vector<Vertex> nodevector = graph.getAdjacent(var);
		
		for(unsigned int i = 0; i < nodevector.size(); i++)
		{
		
			if(graph.getVertexLabel(nodevector[i])!="VISITED" && graph.getEdgeLabel(var,nodevector[i])=="UNEXPLORED")
			{
				graph.setEdgeLabel(var,nodevector[i],"DISCOVERY");
				graph.setVertexLabel(nodevector[i],"VISITED");
				q.push(nodevector[i]);

				distance[nodevector[i]] = distance[var] + 1;
				p[nodevector[i]] = var;

				
			}

			else 
			{
				if(graph.getEdgeLabel(var,nodevector[i]) == "")
				{
					graph.setEdgeLabel(var,nodevector[i],"CROSS");
	
				}
			}

		}

	}
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
    int retval = 10000;
	// mark every edge unexplored
    // mark every node unexplored
    // declare STL queue

    vector<Edge> edges = graph.getEdges();
	vector<Vertex> v   = graph.getVertices();

	for(unsigned int i = 0; i < v.size(); i++)
	{
		graph.setVertexLabel(v[i],"");
	}
	for(unsigned int i = 0; i < edges.size(); i++)
	{
		graph.setEdgeLabel(edges[i].source,edges[i].dest,"UNEXPLORED");
	}
    queue<Vertex> q;
    // invokeBFS
    findMinWeight(graph,q,retval);

	return retval;
}

void GraphTools::findMinWeight(Graph & graph, queue<Vertex> & q, int & retval)
{
	Vertex var = graph.getStartingVertex();

	vector<Vertex> minedge;

	q.push(var);

	graph.setVertexLabel(var,"VISITED");

	while(!q.empty())
	{
		var = q.front();
		q.pop();

		

		vector<Vertex> nodevector = graph.getAdjacent(var);

		for(unsigned int i = 0; i < nodevector.size(); i++)
		{
			int tempret = graph.getEdgeWeight(var,nodevector[i]);
			if(graph.getVertexLabel(nodevector[i])!="VISITED" && graph.getEdgeLabel(var,nodevector[i])=="UNEXPLORED")
			{
				graph.setEdgeLabel(var,nodevector[i],"DISCOVERY");
				graph.setVertexLabel(nodevector[i],"VISITED");
				q.push(nodevector[i]);

				if(tempret < retval)
				{
					while(!minedge.empty())
					{
						minedge.pop_back();
					}

					minedge.push_back(var);
					minedge.push_back(nodevector[i]);
					retval = tempret;
				}
			}
			else if(graph.getEdgeLabel(var,nodevector[i]) == "")
			{
				graph.setEdgeLabel(var,nodevector[i],"CROSS");
				if(tempret < retval)
				{
					while(!minedge.empty())
					{
						minedge.pop_back();
					}

					minedge.push_back(var);
					minedge.push_back(nodevector[i]);
					retval = tempret;
				}
			}
			else;
		}

	}

	graph.setEdgeLabel(minedge[0],minedge[1],"MIN");
}
/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	// get all the edges in the graph

	vector<Edge> lines = graph.getEdges();
	vector<Vertex> v = graph.getVertices();
	// store it in a vector called lines

	// sort them
	sort(lines.begin(),lines.end());
	// create a disjoint set where each vertex is represented by a set
	DisjointSets vset;

	vset.addelements(v.size());
	/* Traverse lines vector from lowest to highest
		
		// if the edge connects two vertices from 'different sets' then union them and label as "MST"

		// repeat until n-1 edges have been added where n is the number of nodes
	 */
	int counter = 1;
	int i = 0;
	while(counter < v.size())
	{
		Edge temp = lines[i];

		Vertex u = temp.source;
		Vertex v = temp.dest;

		if(vset.find(u)!=vset.find(v))
		{
			vset.setunion(u,v);
			graph.setEdgeLabel(u,v,"MST");
			counter++;
		}
		i++;
	}	

}
