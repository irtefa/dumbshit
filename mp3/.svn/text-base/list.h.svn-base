/**
 * Doubly Linked List (MP 3)
 * Created by Chase Geigle for CS225, Fall 2011
 * Modified by Jack Toole (Fall 2011), Chase Geigle (Spring 2012)
 */
#ifndef _LIST_H_
#define _LIST_H_

#include <iterator>
#include <ostream>
#include <algorithm>

using namespace std;

/**
 * List<T> class
 * This is a templated linked list class (meaning it contains data of
 * templated type T, which is a placeholder for a type).
 *
 * You should not remove anything from this class definition, but
 * you will find it helpful to add your own helper functions to this class,
 * and are encouraged to add to it.
 */
template <class T>
class List
{
	private:
		/**
		 * ListNode class
		 * The ListNode class is private to the List class via the principle of
		 * encapsulation---the end user does not need to know our node-based
		 * implementation details.
		 */
		class ListNode
		{
			public:
			/**
			 * ListNode constructors. Implemented for you.
			 * @see list_given.cpp
			 */
			ListNode();
			ListNode(T const & ndata);

			// member variables
			ListNode * next;
			ListNode * prev;
			T const data; // const because we do not want to modify node's data
		};

	public:
		/**
		 * These functions are provided for you.
		 *	- public: Default constructor
		 *	- public: Copy constructor
		 *	- public: Assignment operator
		 *	- public: Size getter
		 *	- public: Printing helper
		 *	- public: Emptiness checker
		 * @see list_given.cpp
		 */
		/**
		 * Default List constructor. 
		 * Creates an empty List. Implemented for you.
		 */
		List();

		/**
		 * Copy constructor for a List. 
		 * Since Lists allocate dynamic memory (i.e., they use "new", we
		 * must define the Big Three).
		 *
		 * @param other The list we are copying.
		 */
		List(const List<T> & other); 

		/**
		 * Overloaded assignment operator for Lists.
		 * Part of the Big Three that we must define because the class
		 * allocates dynamic memory.
		 *
		 * @param rhs The right hand side of the assignment statement.
		 */
		List<T> & operator=(const List<T> & rhs);

		/**
		 * Gets the size of the List.
		 * Defined as a const function because it promises not to modify 
		 * the current List in any way.
		 *
		 * @return The size of the current List.
		 */
		int size() const;

		/**
		 * Used to print the list. 
		 * Const because it promises not to modify the current List.
		 *
		 * @param os Output stream to print the list to (e.g. cout)
		 */
		void print(ostream & os) const;

		/**
		 * Determines if the current List is empty. 
		 * Const because it promises not to modify the current List.
		 *
		 * @return Boolean value of whether the current List is empty.
		 */
		bool empty() const;


		/**
		 * These functions are graded as part of MP3.1.
		 *	- public: List destructor
		 *	- public: insertFront()
		 *	- public: insertBack()
		 *	- public: reverse()
		 *	- public: reverseNth()
		 *	- public: waterfall()
		 */

		/**
		 * ~List() -- Destructor
		 * Destroys the current list.
		 */
		~List();

		/**
		 * insertFront() -- Insertion function
		 * Inserts a new node at the front of the list.
		 *
		 * @param ndata Data to be inserted.
		 */
		void insertFront(const T & ndata);

		/**
		 * insertBack() -- Insertion function
		 * Inserts a new node at the back of the list.
		 *
		 * @param ndata Data to be inserted.
		 */
		void insertBack(const T & ndata);

		/**
		 * reverse() -- Reversal function
		 * Reverses the given list.
		 */
		void reverse();

		/**
		 * reverseNth() -- Reversal function
		 * Reverses every N elements in the list.
		 *
		 * @param n The size of the blocks in the list to be reversed.
		 */
		void reverseNth(int n);

		/**
		 * waterfall() -- Effect function
		 * Modifies the list using the waterfall algorithm.
		 */
		void waterfall();


		/**
		 * These functions are graded as part of MP3.2.
		 *	- public: split()
		 *	- public: merge()
		 *	- public: sort()
		 */

		/**
		 * split() -- Splitting function
		 * Splits the given list into two parts by dividing it at the
		 * splitPoint.
		 *
		 * @param splitPoint Point at which the list should be split into two.
		 * @return The second list created from the split.
		 */
		List<T> split(int splitPoint);

		/**
		 * mergeWith() -- Merging function
		 * Merges the given sorted list into the current sorted list.
		 *
		 * @param otherList List to be merged into the current list.
		 */
		void mergeWith(List<T> & otherList);

		/**
		 * sort() -- Mergesort Sorting Function
		 * Sorts the current list by applying the Mergesort algorithm.
		 */
		void sort();

		// Provided Iterator Functions
		#include "list_given.h"

	private:
		/**
		 * Private member variables.
		 *
		 * You must use these as specified in the spec and may not rename them.
		 * You may add more if you need them.
		 */
		ListNode * head;
		ListNode * tail;
		int length;

		/**
		 * Private helper functions.
		 *
		 * You must use these as specified in the spec and may not rename them.
		 * You may place more here as you need them.
		 * @see list.cpp
		 */
		void copy(List<T> const & other); // implemented in list_given.cpp
		void clear();
		static void reverse(ListNode * & head, ListNode * & tail);
		static ListNode * split(ListNode * start, int splitPoint);
		static ListNode * merge(ListNode * first, ListNode * second);
		static ListNode * mergesort(ListNode * start, int size);
};

// needed for template instantiation
#include "list.cpp"

// this includes all of the functions that are given to you
// (i.e., the ones that you do not need to implement)
#include "list_given.cpp"

#endif
