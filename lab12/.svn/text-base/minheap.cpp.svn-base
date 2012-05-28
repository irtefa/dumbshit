#include <iostream>
#include <algorithm>

using namespace std;


// buildHeap
//	 - transforms the input array to have the properties of a heap
template <class T>
void buildHeap(vector<T> & array)
{
	// Your code here
	for(unsigned int i= 0; i < array.size(); i++)
	{
		heapifyUp(array,i);
	}
}


// removeMin
//	- returns an element of type T that is the least
//	  element in the heap.  
//	- removes that element from the heap and reheapifies 
template <class T>
T removeMin(vector<T> & array)
{
	if (array.empty())
	{
		std::cout << "empty heap" << std::endl;
		return T();
	}

	T temp = array[0];
	array[0] = array.back();
	array.pop_back();
	heapifyDown(array, 0);
	return temp;
}


// heapInsert
//	- insElem - the item to be inserted into the minHeap
//	- performs the insert and reheapifies
template <class T>
void heapInsert(vector<T> & array, T const & insElem)
{
	array.push_back(insElem);
	heapifyUp(array, array.size()-1);
}


// heapifyDown
//  - helper function traverses tree restoring heap property
template<class T>
void heapifyDown(vector<T> & array, int cIndex)
{
	// Your code here
	// if has child
	if(hasChild(array, cIndex))
	{
		// assign temp to that child
		int minchild = minChild(array, cIndex);
		if(array[cIndex] > array[minchild])
		{
			//swap em
			swap(array[cIndex], array[minchild]);
			//heapify down
			heapifyDown(array,minchild);
		}
	}
}

// heapifyUp
//  - helper function traverses tree restoring heap property
template<class T>
void heapifyUp(vector<T> & array, int cIndex)
{
	if (cIndex > 0)
	{
		int tempParent = parent(array, cIndex);
		if (array[cIndex] < array[tempParent])
		{
			swap(array[cIndex], array[tempParent]);
			heapifyUp(array, tempParent);
		}
	}
}

// parent
//  - returns the index of the parent of cIndex
template<class T>
inline int parent(const vector<T> & array, int cIndex)
{
	return (cIndex+1)/2-1;
}


// rightChild 
//  - returns the index of the right child of cIndex
template<class T>
inline int rightChild(const vector<T> & array, int cIndex)
{
	return 2*(cIndex+1);
}

// leftChild 
//  - returns the index of the left child of cIndex
template<class T>
inline int leftChild(const vector<T> & array, int cIndex)
{
	return 2*(cIndex+1)-1;
}

// print
//  - prints out the heap's array
template<class T>
void print(const vector<T> & array)
{
	std::cout << "[ ";
	for (unsigned int i = 0; i < array.size(); i++)
		std::cout << array[i] << ' ';
	std::cout << ']';
}

// Helpers I wrote 

template<class T>
bool hasChild(const vector<T> & array, int cIndex) 
{
	if(leftChild(array,cIndex) < array.size() || rightChild(array,cIndex) < array.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
int minChild(const vector<T> & array, int cIndex) 
{
	int left  = leftChild(array, cIndex);
	int right = rightChild(array,cIndex);

	if(left < array.size() && array[left] < array[right])
	{
		return left;
	}
	else
	{
		return right;
	}
}