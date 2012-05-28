// *****************************************************
// *                                                   *
// *  heap.h                                           *
// *                                                   *
// *  Interface for a simple generalized (template)    *
// *    min-heap class, where the values of the        *
// *    generic type that are being stored, are        *
// *    also the priorities.                           *
// *                                                   *
// *  Written October 2005 by Jason Zych               *
// *  Modified October 2007 by Cinda Heeren            *
// *  Modified November 2010 by Jack Toole             *
// *                                                   * 
// *****************************************************

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
using std::vector;


// MinHeap
//	 - constructor
//	 - parameters : oneDatum - a single piece of data 
//	 - initializes the heap vector and places the data elt in 
//     cell 1.
template <typename T>
void buildHeap(vector<T> & array);

// removeMin
//	 - return value : an element in the heap 
//	 - removes the element in the heap with the minimum priority,
//			and returns it; an assertion is triggered if the heap
//			is empty
template <typename T>
T removeMin(vector<T> & array);


// insert
//	 - parameters : insElem - the item to be inserted into the
//							 min-heap
//	 - inserts the parameter item into the min-heap
template <typename T>
void heapInsert(vector<T> & array, T const & insElem);


// print
//	 - prints out the heap's array
template <typename T>
void print(const vector<T> & array);

// private helper functions
template <typename T>
void heapifyUp(vector<T> & array, int cIndex);

template <typename T>
void heapifyDown(vector<T> & array, int cIndex);

template <typename T>
int leftChild(const vector<T> & array, int cIndex);

template <typename T>
int rightChild(const vector<T> & array, int cIndex);

template <typename T>
int parent(const vector<T> & array, int cIndex);

// HELPERS

template <typename T>
bool hasChild(const vector<T> & array, int cIndex) ;

template <typename T>
int minChild(const vector<T> & array, int cIndex) ;

#include "minheap.cpp"
#endif

