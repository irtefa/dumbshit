/* kdtree.h
 * KDTree implementation using Points in k-dimensional space.
 *		   
 * Written by Cinda Heeren for CS225 MP6
 * Spring 2009
 *		   
 * Revision history:
 * 3/31/2009        Created
 * 11/10/2009       Modified for MP6 Submission, Fall 2009
 * Spring 2011      Modified for MP6.1 release by Jack Toole
*/
		   
#ifndef __KDTREE_H__
#define __KDTREE_H__
		   
#include <iostream>
#include <string>
#include <vector>
#include "coloredout.h"
#include "point.h"
#include <math.h>
using namespace std;

template<int Dim>
class KDTree
{
	private:
	// Member variables
	vector< Point<Dim> > points;
	vector<int> point_index;
	// You may add your own member variables here

	// You may add your own helper functions here
	 class PointComp
    {
      public:
		PointComp(vector< Point<Dim> > & arrIn, int dimIn)
		{
	  		pointArray = arrIn;
	  		dimension = dimIn;
		}
		bool operator()(int idx1, int idx2)
		{
	  		if(((pointArray)[idx1])[dimension] < ((pointArray)[idx2])[dimension])
	  		{
	    		return true;
	  		}
	  		else if(((pointArray)[idx1])[dimension] > ((pointArray)[idx2])[dimension])
	  		{	
	    		return false;
	    	}//*/
	    	else
	    	{
	    		return ((pointArray)[idx1]) < ((pointArray)[idx2]);
	    	}
		}
     private:
		vector< Point<Dim> > pointArray;
		int dimension;
    };

	// Print helper functions
	int  getPrintData(int low, int high) const;
	void printTree(int low, int high, vector<string> & output,
				   int left, int top, int width, int currd) const;

	public:

	// Print functions
	void printVectors(ostream & out = cout,
			 colored_out::enable_t enable_bold = colored_out::COUT) const;

	void printTree(ostream & out = cout,
				   colored_out::enable_t enable_bold = colored_out::COUT,
				   int modWidth = -1) const;

	void gradingPrint(ostream & out) const;
	
	// MP 6.1 functions
	bool smallerDimVal(const Point<Dim> & a, const Point<Dim> & b, int d) const;
	
	bool shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const;
	
	KDTree(const vector< Point<Dim> > & newPoints);

	Point<Dim> findNearestNeighbor(const Point<Dim> & a) const;
	
	// helpers
	double distance(const Point<Dim> & p1, const Point<Dim> & p2) const;
	void buildTree(int left, int right, int d);
	Point<Dim> nns(int lo,int hi,const Point<Dim> & a, int d) const;
	double locdistance(int const & d, const Point<Dim> & p1, const Point<Dim> & p2) const;
};

// ******
// DO NOT REMOVE THESE LINES
// ******
#include "kdtree.cpp"
#include "kdtree_extras.cpp"

#endif

