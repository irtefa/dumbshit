/* kdtree.cpp
 * Implementation of KDTree class
 *		   
 * Written by Cinda Heeren for CS225 MP6
 * Spring 2009
 * Revision history:
 * 3/31/2009        Created
 * Spring 2011      Modified by Jack Toole
*/
		   

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & a, const Point<Dim> & b, int d) const
{
	// Your code here
	if(a[d] < b[d])
	{
		return true;
	}
	else if(a[d]==b[d])
	{
		return a < b;
	}
	else 
	{
		return false;
	}
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{

	double pottar = distance(target, potential);
	double curtar = distance(target, currentBest);

	if(pottar < curtar)
	{
		return true;
	}
	else if(pottar > curtar)
	{
		return false;
	}
	else
	{
		return potential < currentBest;
	}  
	//return false;// Your code here
}


template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)

{
	points = newPoints;

	for(int i = points.size() -1;i >= 0;i--)
	{
		point_index.push_back(i);
	}

	buildTree(0, points.size(), 0);// call helper function here
}


template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & a) const
{
	return nns(0,points.size()-1,a,0); // Replace with your code
}


/*
 * Helper for the findNearestNeighbor
 */


template<int Dim>
Point<Dim> KDTree<Dim>::nns(int lo,int hi,const Point<Dim> & target,int d) const
{
	
	/*
     * Base case : If it is the leaf
     */

	 if(lo>=hi)
	 {
		return points[point_index[lo]];
	 }

	int median = (lo + hi) / 2;

	Point<Dim> leaf;
	Point<Dim> curr = points[point_index[median]];

	Point<Dim> best;

	// checks the leaf

	if(smallerDimVal(target,curr,d))
	{
		leaf = nns(lo,median-1,target,(d+1)%Dim);
	}
	else
	{
		leaf = nns(median+1,hi,target,(d+1)%Dim);
	}
	
	// checks if the parent and target's distance is smaller than the child's if it is best = curr

	if(shouldReplace(target,leaf,curr))
	{
		best = curr;
	}
	else
	{
		best = leaf;
	}

	Point<Dim> temp;

	// checks if the child's distance is less than that of the parent's. If it is less, then go visit them

	if(distance(best,target) >= locdistance(d,target,curr))
	{
		if(smallerDimVal(target,curr,d))
		{
			temp = nns(median+1,hi,target,(d+1)%Dim);
		}
		else
		{
			temp = nns(lo,median-1,target,(d+1)%Dim);
		}
		
		if(shouldReplace(target,best,temp))
		{
			best = temp;
		}
	}

	return best;
}
/*
 * KDTree Helper Functions
 */

template<int Dim>
double KDTree<Dim>::distance(const Point<Dim> & p1,const Point<Dim> & p2) const
{
	double retval = 0;
	int dim = Dim;
	for(int i=0;i < dim;i++)
	{
	 retval += (p1[i]-p2[i]) * (p1[i] - p2[i]);
	}
	
	return retval;
}

template<int Dim>
double KDTree<Dim>::locdistance(int const & d, const Point<Dim> & p1, const Point<Dim> & p2) const
{
	return ((p1[d] - p2[d]) * (p1[d] - p2[d]));  
}

template<int Dim>
void KDTree<Dim>::buildTree(int left, int right, int d)
{

	if(left >= (right-1))
	{
		return;
	}

	int median = ((left + right - 1) / 2);
	int dim = d % Dim;
	PointComp comparator(points, dim);

	sort(point_index.begin() + left, point_index.begin() + right, comparator);

	buildTree(left, median, d + 1);
	buildTree(median+1, right, d + 1);
}
