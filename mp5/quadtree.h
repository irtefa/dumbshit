// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "easypng.h"

class Quadtree
{
	public:
		Quadtree();
		Quadtree(PNG & src, int d);
		Quadtree(const Quadtree & src);
		~Quadtree();
		Quadtree const & operator=(const Quadtree & rhs);
		void buildTree(PNG & src, int d);
		RGBAPixel getPixel(int x, int y);
		PNG decompress();
		void clockwiseRotate();
		void prune(int tolerance);
		int pruneSize(int tolerance);
		int idealPrune(int numLeaves);	
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
	    QuadtreeNode();     // default constructor	
		QuadtreeNode(RGBAPixel  pixelobj);
		bool isEmpty() const;
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	int dimension;			// stores the dimension of the tree

	
	/**** Functions added for testing/grading                ****/
		//void decompress(QuadtreeNode * const & node, PNG & obj);
	
		// MP 5.1 Helpers
		void decompress(QuadtreeNode * const & node, PNG & obj, int d, int x, int y);
		RGBAPixel getPixel(int d, int x, int y, QuadtreeNode * & node);	
		void QuadtreeBuilder(PNG & src,int d, int x, int y,QuadtreeNode * & node);
		void _copy(QuadtreeNode  * const &  other, QuadtreeNode * & node);
		void _clear(QuadtreeNode * & node);

		// Helper functions to find the average
		int _red(QuadtreeNode * & a, QuadtreeNode * & b, QuadtreeNode * & c, QuadtreeNode * & d);
		int _green(QuadtreeNode * &a, QuadtreeNode * &b, QuadtreeNode * &c, QuadtreeNode * &d);
		int _blue(QuadtreeNode * &a, QuadtreeNode * &b, QuadtreeNode * &c, QuadtreeNode * &d);
		
		// 5.2

		// Clockwise Rotation Helper
		void clockwiseRotate(QuadtreeNode * & node);
		
		// Prune Helpers
		void prune(int tol, QuadtreeNode * & node);
		int _diff(RGBAPixel now, RGBAPixel init);
		int difference(RGBAPixel average, QuadtreeNode * & node);

		// PruenSize Helper
		int _prunedLeaves(int tol, QuadtreeNode * & node);
		int _leaves(QuadtreeNode * & node) const;
		//int pruneSize(QuadtreeNode * & node, int tolerance);

		// idealPrune Helper
		int findNum(int numLeaves, int lo, int hi) ;
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
