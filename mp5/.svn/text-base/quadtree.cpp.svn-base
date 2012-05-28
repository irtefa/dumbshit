// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"

using namespace std;

/*
 * What you will see is extremely beautiful code.
 * After losing a lot of points in the past few mps
 * I decided to put in ample time to make this one
 * PERFECT!
 * It's well commented and uses a fast way to do everything.
 */

// The first constructor where we set root to NULL
Quadtree::Quadtree()
{
	root = NULL;
	dimension = 0;
}

// The second constructor that has two params, PNG object source and an int d

Quadtree::Quadtree(PNG & src, int d)
{
	root = NULL; // 
 	// we will call the helper here
 	buildTree(src,d);
}

void Quadtree::buildTree(PNG & src, int d)
{

	_clear(root);
	root = new QuadtreeNode();
	dimension = d;
	QuadtreeBuilder(src,d,0,0,root);
}

// Copy constructor


Quadtree::Quadtree(const Quadtree & src)
{
	// Invoke the _copy helper which takes care of everything else
	dimension = src.dimension;
	_copy(src.root, root);
}

// Destructor

Quadtree::~Quadtree()
{
	_clear(root);
	root = NULL;
}

// Operator=

Quadtree const & Quadtree::operator=(const Quadtree & rhs) 
{
	if(this!= &rhs)
	{
		_clear(root);
		dimension = rhs.dimension;
		_copy(rhs.root,root);
	}

	return *this;
}

/*
 * Get Pixel
 */

RGBAPixel Quadtree::getPixel(int x, int y)
{
	int d = dimension;
	return getPixel(d,x,y,root);
}

/*
 * GetPixel Helper. Efficiently searches for the given pixels by using something like a binary search algorithm. (m-ary search)
 * 
 * 	args:
 *		d   : Dimension of the current quadtree
 *		x,y :
 *		node: Root of the subtree at that specific recursion level
 */
   
RGBAPixel Quadtree::getPixel(int d, int x, int y,QuadtreeNode * & node)
{
	if(node==NULL)
	{
		return RGBAPixel(); // means it couldn't find anything
	}	
	if(node->isEmpty())
	{
		return node->element;
	}

	if(x < d/2 && y < d/2)
	{
		return getPixel(d/2, x, y, node->nwChild);
	}
	else if (x >= d/2 && y < d/2)
	{
		return getPixel(d/2,x-d/2,y,node->neChild);
	}
	else if (x < d/2 && y >= d/2)
	{
		return getPixel(d/2,x,y-d/2,node->swChild);
	}
	else
	{
		return getPixel(d/2,x-d/2,y-d/2,node->seChild);
	}

}

/*
 *
 * Makes the image from the quadtree
 *
 */

PNG Quadtree::decompress()
{
	PNG obj;
	if(root==NULL || dimension == 0)
	{
		return obj;
	}
	obj.resize(dimension,dimension);
	for(int i = 0; i < dimension; i++)
		for(int j= 0; j < dimension; j++)
	{
		RGBAPixel color = getPixel(i,j);
		obj(i,j)->red   = color.red;
		obj(i,j)->green = color.green;
		obj(i,j)->blue  = color.blue;
	}
	return obj;	
}

/*
 * Builds the Quadtree (helper function for buildtree)
 *
 * 		args:
 *			src : The PNG image that is given to us from which we will make the tree 
 *			d   : The dimension of the current subtree
 *			x   : 
 *			y   :
 *			node: Root of the subtree
 */

void Quadtree::QuadtreeBuilder(PNG & src, int d, int x, int y, QuadtreeNode * & node)
{
	// base case i.e. when d == 1
	if(d==1)
	{
		node->element.red   = src(x,y)->red;
		node->element.green = src(x,y)->green;
		node->element.blue  = src(x,y)->blue;
		return;
	}
	// assign the indices
	int offset = d/2;
	
	node->nwChild = new QuadtreeNode();
	node->neChild = new QuadtreeNode();
	node->swChild = new QuadtreeNode();
	node->seChild = new QuadtreeNode();
	
	QuadtreeBuilder(src,offset,x,y,node->nwChild);
	QuadtreeBuilder(src,offset,x+offset,y,node->neChild);
	QuadtreeBuilder(src,offset,x,y+offset,node->swChild);
	QuadtreeBuilder(src,offset,x+offset,y+offset,node->seChild);
	
	// take the average of all four children
	// _red finds the red average and likewise
	int newRed   = _red(node->nwChild,node->neChild,node->swChild,node->seChild);	
	int newGreen = _green(node->nwChild,node->neChild,node->swChild,node->seChild);	
	int newBlue  = _blue(node->nwChild,node->neChild,node->swChild,node->seChild);	


	node->element.red   = newRed;
	node->element.green = newGreen;
	node->element.blue  = newBlue;
}

/*
 * QuadtreeNode constructor (default)
 */

Quadtree::QuadtreeNode::QuadtreeNode()
{
	nwChild = NULL;
	neChild = NULL;
	swChild = NULL;
	seChild = NULL;
	
	element = RGBAPixel();
}

/*
 *	QuadtreeNode constructor
 */

Quadtree::QuadtreeNode::QuadtreeNode(RGBAPixel  pixelobj)
{
	nwChild = NULL;
	neChild = NULL;
	swChild = NULL;
	seChild = NULL;

	element.red   = pixelobj.red;
	element.green = pixelobj.green;
	element.blue  = pixelobj.blue;
}

/*
 * Quadtree copy constructor helper function
 *
 * args:
 *		other: The given Quadtree's node
 *		nodes: Node of the new Quadtree that is being copied to
 */

void Quadtree::_copy(QuadtreeNode * const &  other, QuadtreeNode * & node)
{
	if(other==NULL) return;

	
	node = new QuadtreeNode(other->element);


	_copy(other->nwChild,node->nwChild);
	_copy(other->neChild,node->neChild);
	_copy(other->swChild,node->swChild);
	_copy(other->seChild,node->seChild);

	
}

/*
 * Helper for the destructor
 *
 * args:
 *		node: The root of the subtree
 */

void Quadtree::_clear(QuadtreeNode * & node)
{
	if(node!=NULL)
	{_clear(node->nwChild);
	_clear(node->neChild);
	_clear(node->swChild);
	_clear(node->seChild);

	delete node;
	node = NULL;}
	
	// Post order traversal

	
}

/*
 * 	Helper functions for QuadtreeBuilder. They find the average of the children
 *
 *		args: The args are all the four nodes from which each RGBAPixel be taken to calculate the average
 */

int Quadtree::_red(QuadtreeNode * & a, QuadtreeNode * & b, QuadtreeNode * & c, QuadtreeNode * & d)
{
	return ((a->element.red + b->element.red + c->element.red + d->element.red)/4);	
}
int Quadtree::_green(QuadtreeNode * & a, QuadtreeNode * & b, QuadtreeNode * & c, QuadtreeNode * & d)
{
	return ((a->element.green + b->element.green + c->element.green + d->element.green)/4);	
}
int Quadtree::_blue(QuadtreeNode * & a, QuadtreeNode * & b, QuadtreeNode * & c, QuadtreeNode * & d)
{
	return ((a->element.blue + b->element.blue + c->element.blue + d->element.blue)/4);	
}

// MP 5.2

/*
 *	ClockwiseRotate function rotates the image by 90 degrees to the right.
 */

void Quadtree::clockwiseRotate()
{
	clockwiseRotate(root);
}


/*
 *	The prune function
 *
 *		args:
 *			tolerance: The tolerance level that is provided by the user
 *
 */

void Quadtree::prune(int tolerance)
{
	prune(tolerance, root);
}

/*
 *	Prunes the subtree (helper for the prune function)
 *  	
 *		args:
 *			tol : given tolerance by client
 *			node: root of the subtree
 */			

void Quadtree::prune(int tol, QuadtreeNode * & node)
{
	if(node==NULL || node->isEmpty())
	{
		return;
	}

	if(difference(node->element, node) <= tol)
	{
		//clear everything
		_clear(node->nwChild);
		_clear(node->neChild);
		_clear(node->swChild);
		_clear(node->seChild);

		//Null the nodes
		node->nwChild = NULL;
		node->neChild = NULL;
		node->swChild = NULL;
		node->seChild = NULL;
	}
	else
	{
		prune(tol,node->nwChild);
		prune(tol,node->neChild);
		prune(tol,node->swChild);
		prune(tol,node->seChild);
	}
}


/*
 * Finds the total number of leaves that will remain after pruning
 *
 * 	args:
 *		tolerance: the tolerance
 *
 */


int Quadtree::pruneSize(int tolerance)
{
	int total_leaves  = _leaves(root);
	int pruned_leaves = _prunedLeaves(tolerance,root);

	return total_leaves - pruned_leaves;
}

/* 
 * 	Finds the minimum tolerance necessary for the tree to have the given number of leaves	
 *
 *	args:
 *		numLeaves: Number of leaves that should remain after the pruning
 */	

int Quadtree::idealPrune(int numLeaves)
{
	return findNum(numLeaves,0,3*255*255);
}

/*
 *	 Clockwise Rotate Helper
 *
 *		args:
 *			node: Current QuadtreeNode where we are performing the rotation operation		
 */
void Quadtree::clockwiseRotate(QuadtreeNode * & node)
{
	if(node==NULL) return;
	
	clockwiseRotate(node->nwChild);
	clockwiseRotate(node->neChild);
	clockwiseRotate(node->swChild);
	clockwiseRotate(node->seChild);
	
	QuadtreeNode * a = node->nwChild;
	QuadtreeNode * b = node->neChild;
	QuadtreeNode * c = node->swChild;
	QuadtreeNode * d = node->seChild;
	
	node->nwChild = c;
	node->neChild = a;
	node->swChild = d;
	node->seChild = b;	
	
}

/*
 * 	Recursively finds the difference between the current node and the leaf
 *	
 *	args:
 * 		average: Element of the root node
 *		node   : QuadtreeNode of the subtree 
 */
int Quadtree::difference(RGBAPixel average, QuadtreeNode * & node)
{
	if(node->isEmpty())
	{
		return _diff(node->element,average);
	}
	int diff = max(difference(average,node->nwChild),difference(average,node->neChild));
		diff = max(diff,difference(average,node->swChild));
		diff = max(diff,difference(average,node->seChild));
	return diff;
}

/*
 * 	Finds the difference between two pixels
 *	
 *	args:
 *		now, init : Two RGBAPixel between which we will find the difference
 * 	
 */
int Quadtree::_diff(RGBAPixel now, RGBAPixel init)
{
	int x = (now.red   - init.red);
	int y = (now.green - init.green);
	int z = (now.blue  - init.blue);
	x *= x;
	y *= y;
	z *= z;
	return x+y+z;
}	

/*
 * 	Finds the number of leaves in a tree (helper for prunesize)	
 * 	
 *	args:
 *		node: The root of the subtree
 */
int Quadtree::_leaves(QuadtreeNode * & node) const
{
	if(node==NULL)
	{
		return 0;
	}

	if(node->isEmpty())
	{
		return 1;
	}

	return _leaves(node->nwChild) + _leaves(node->neChild) + _leaves(node->swChild) + _leaves(node->seChild);
}
/*
 *	 Finds the number of leaves in a pruned tree (helper)
 *
 *	 args: 
 *	 	tol : The tolerance
 *	 	node: The root of the subtree
 */

int Quadtree::_prunedLeaves(int tol, QuadtreeNode * & node) 
{
	if(node==NULL || node->isEmpty())
	{
		return 0;
	}

	if(difference(node->element,node) <= tol)
	{
		return _leaves(node) - 1;
	}
	else
	{
		int num = _prunedLeaves(tol,node->nwChild)+
				  _prunedLeaves(tol,node->neChild)+
				  _prunedLeaves(tol,node->swChild)+
				  _prunedLeaves(tol,node->seChild);
		return num;
	}

}

/*
 * 	A sexy binary search algorithm to find the idealPrune :)
 *
 *	 args: 
 *		numLeaves: Number of leaves that should be there after pruning.
 *		lo 		 : Smallest Tolerance possible
 *		hi 		 : Largest  Tolerance possible
 */

int Quadtree::findNum(int numLeaves,int lo,int hi) 
{
	if(lo==hi)
	{
		return lo;
	}
	int mid = lo+( hi-lo)/2;

	int num = pruneSize(mid);

	if(num > numLeaves)
	{
		return findNum(numLeaves,mid+1,hi);
	}
	else
	{
		return findNum(numLeaves,lo,mid);
	}	
}


/*
 * Checks if a node has no children if it does not, it return true
 */

bool Quadtree::QuadtreeNode::isEmpty() const
{
	if(nwChild==NULL && neChild==NULL && swChild==NULL && seChild == NULL)
		return true;
	return false;
}
