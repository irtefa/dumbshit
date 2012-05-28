#include <iostream>
using namespace std;

/**
 * Doubly Linked List (MP 3)
 * Created by Chase Geigle for CS225 (Fall 2011)
 * Modified by Jack Toole (Fall 2011), Chase Geigle (Spring 2012)
 */

/**
 * ~List() -- Destructor (Graded in MP3.1)
 * 
 * Destroys the current list.
 * This function should ensure that memory does not leak on destruction of
 * a list.
 */
template <class T>
List<T>::~List()
{
	clear();// your code here
}

/**
 * clear() -- Private Helper (Graded in MP3.1)
 *
 * Clears the current list.
 * This function is called to ensure that memory associated with the
 * current list is completely freed.
 */
template <class T>
void List<T>::clear()
{
	if(length>0)
	{
	ListNode * curr;
	ListNode * tmp;
	if(head!=tail)	
	{
		curr = head;
		while(curr!=tail)
		{
			tmp = curr->next;
			delete head;
			curr = tmp;
			head = curr;
		}
		delete tmp;
	}

		head = NULL;
		tail = NULL;
		length = 0;		
	
	}
}

/**
 * insertFront() -- Insertion Function (Graded in MP3.1)
 *
 * Inserts a node with the parameter value into the list at the front.
 * This function SHOULD create a new ListNode.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
	ListNode *newNode;

	newNode = new ListNode(ndata);
	
	if(head!=NULL)				 // checking if the list is empty
	{
		head->prev    = newNode; // 1
		newNode->next = head;    // 2
		head          = newNode; // 3
		length++;
	}
	else
	{
		head = newNode;
		head->next = NULL;
		head->prev = NULL;
		tail = newNode;
		length++;
	}

}

/**
 * insertBack() -- Insertion Function (Graded in MP3.1)
 *
 * Inserts a node with the parameter value into the list at the back.
 * This function SHOULD create a new ListNode.
 */
template <class T>
void List<T>::insertBack(T const & ndata)
{
	
	ListNode *newNode;
	newNode = new ListNode(ndata);
	if(head!=NULL)              // checking if the list is empty
	{
		tail->next    = newNode;
		newNode->prev = tail;
		tail          = newNode;
		length++;				// incrementing the size of the list after each addition
	}
	else
	{
		head = newNode;
		head->next = NULL;
		head->prev = NULL;
		tail = newNode;
		length++;
	}
}


/**
 * reverse() -- Public Reversal Function
 *
 * Reverses the current list.
 */
template <class T>
void List<T>::reverse()
{
	reverse(head, tail);
}

/**
 * reverse() -- Private Reversal Helper (Graded in MP3.1)
 *
 * Reverses the partial list delimited by the supplied pointers.
 * This function should impact the head and tail pointers as well (use the
 * references to change where they point from inside this function).
 *
 * @param head Reference to a pointer to the head of the sublist to be reversed.
 * @param tail Reference to a pointer to the tail of the sublist to be reversed.
 */
template <class T>
void List<T>::reverse(ListNode * & head, ListNode * & tail)
{
	if(head==NULL || head==tail)
		return;
		
	ListNode * curr = head->next;
	ListNode * t1, *tmp;
	ListNode * t2;
	while(curr!=tail)
	{

		tmp = curr->next;
		curr->next = curr->prev;
		curr->prev = tmp;
		curr= curr->prev;
	}
	
	t1 = head->next;
	head ->next = tail->next;
	t2 = head->prev;
	head->prev = t1;
	t1 = tail->prev;
	tail->prev = t2;
	tail->next = t1;
	

	
	tmp = tail;
	tail = head;
	head = tmp;
}
	

/**
 * reverseNth() -- Public Block Reversal Function (Graded in MP3.1)
 * 
 * Reverses the current list in blocks of the given size.
 * You should use your reverse() helper function in this method.
 *
 * @param n Size of the blocks to be reversing.
 */
template <class T>
void List<T>::reverseNth(int n)
{
	if(n==0 || n==1 || (length < n))
		return ;
		
	if(length==n)
	{
		reverse(head,tail);
		return;
	}
	
	ListNode * curr = head;
	ListNode * node;
	
	//for(int j = 0; j < 3; j++)
	
	while(curr!=NULL)
	{		
		if(curr==head)
			node = head;
		else
			node = curr->prev;
		int i;
		for(i=0;i < n;i++)
		{
			if(curr!=tail)
				curr=curr->next;
		}

		
		if(node==head)
			reverse(head,curr->prev);
		else if(curr!=tail)
			reverse(node->next,curr->prev);
		else{ 
			reverse(node->next,tail);
			curr = NULL;
		}
	}

}

/**
 * waterfall() -- Public List Reordering Function (Graded in MP3.1)
 *
 * Reorders the current list using the waterfall algorithm.
 */
template <class T>
void List<T>::waterfall()
{
	ListNode * curr = head;
	ListNode * tmp;
	ListNode * holder = head;
	
	while(holder!=NULL && curr->next!=tail)
	{
		tmp = curr->next;
		curr->next = tmp->next;
		tail->next = tmp;
		tmp->prev = tail;
		tmp->next = NULL;
		curr = holder->next;
		tail = tmp;
		holder = holder -> next;
	}
}

/**
 * split() -- Public Splitting Function
 * 
 * Splits the list into two lists after the given number of nodes.
 *
 * @param splitPoint Number of nodes after which to split the list.
 * @return The List that is created after the split point.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
	if (splitPoint > length)
		return List<T>();

	ListNode * secondHead = split(head, splitPoint);

	// set up current list
	tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	int oldLength = length;
	length = splitPoint;
	
	// set up the returned list
	List<T> ret;
	ret.head = secondHead;
	ret.tail = secondHead;
	while (ret.tail->next != NULL)
		ret.tail = ret.tail->next;
	ret.length = oldLength - splitPoint;
	return ret;
}

/**
 * split() -- Splitting Helper Function (Graded in MP3.2)
 *
 * Splits the partial list that starts at the given node after the given
 * number of nodes. In other words, it should disconnect the list after the
 * given number of nodes, and return a pointer to the head of the new
 * partial list.
 *
 * This function SHOULD NOT create ANY new List objects.
 *
 * @param start ListNode denoting the "head" of the partial list to work on.
 * @param splitPoint Desired point to split the list into two. 
 * @return Pointer to the head of the partial list that results from the split.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
	ListNode * curr, *tmp;
	curr = start;
	for(int i=1;i < splitPoint;i++)
	{
		curr = curr->next;
	}
	tmp = curr->next;
	curr->next = NULL;
	return tmp;
}

/**
 * mergeWith() -- Public Merging Function
 *
 * Merges the given list into the current list. Assumes that both lists are
 * sorted.
 *
 * @param otherList List to be merged with. Should be left empty by the function.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
	// set up the current list
	head = merge(head, otherList.head);
	tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	length = length + otherList.length;

	// empty out the parameter list
	otherList.head = NULL;
	otherList.tail = NULL;
	otherList.length = 0;
}

/**
 * merge() -- Merging Helper Function (Graded in MP3.2)
 *
 * Merges two sorted partial lists (starting at first and second
 * respectively) into one partial list. The new partial list should have
 * the data elements in increasing order.
 *
 * This function SHOULD NOT create ANY new List objects.
 *
 * @param first Head of the first sorted partial list
 * @param second Head of the second sorted partial list
 * @return A pointer to the head of the new, merged partial list
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
	ListNode * holder;
	ListNode * reff  ;
	ListNode * curr = first;
	ListNode * tmp = second;
	bool      flag = false;
	
	if(curr==NULL && tmp!=NULL)
	{
		holder = second;
		return holder;
	}
	
	if(tmp==NULL && curr!=NULL)
	{
		holder = first;
		return holder;
	}
	
	if((curr->data) < (tmp->data))
	{
		holder = first;
		curr   = holder;
		curr   = curr->next;
	}
	else
	{
		holder = second;
		tmp    = holder;
		tmp    = tmp->next;
	}
		
	reff = holder;
	
	while(!flag)
	{
		if(curr==NULL && tmp!=NULL)
		{
			reff->next = tmp;
			tmp ->prev = reff;
			reff       = reff-> next;
			tmp        = tmp -> next;
		}
		else if(tmp==NULL && curr!=NULL)
		{
			reff->next = curr;
			curr->prev = reff;
			reff       = reff->next;
			curr       = curr->next;
		}
		else if((curr->data) < (tmp->data))
		{
			reff->next = curr;
			curr->prev = reff;
			reff       = reff->next;
			curr       = curr->next;
		}
		else
		{
			reff->next = tmp;
			tmp->prev  = reff;
			tmp        = tmp->next;
			reff       = reff->next;
		}
		if(curr==NULL && tmp == NULL)
		{
			flag = true;
		}
	}
	//first = holder;	
	//return first;
	return holder;
}

/**
 * sort() -- Mergesort Sorting Function
 *
 * Sorts the current list by applying the Mergesort algorithm.
 * This function (and any helpers it calls):
 * - SHOULD NOT allocate any new memory.
 * - SHOULD NOT create any new Lists.
 * - SHOULD NOT create any new ListNodes.
 *
 * You should implement the given helper functions to solve this.
 */
template <class T>
void List<T>::sort()
{
	if (empty())
		return;
	head = mergesort(head, length);
	tail = head;
	while (tail->next != NULL)
		tail = tail->next;
}

/**
 * mergesort() -- Sorting Helper Function (Graded in MP3.2)
 * 
 * Sorts the partial list given a start node and a size. 
 * This is the recursive helper for the Mergesort algorithm
 * (i.e., this is the divide-and-conquer step).
 * 
 * @param start ListNode denoting the "head" of this partial list.
 * @param size Size of the partial list.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int size)
{
	if(size==1) return start;
	
	ListNode * left;
	ListNode * right;
	int mid = size/2;

	
	left = start;

		
	right = split(start,mid);
	
	left = mergesort(left, mid);
	right = mergesort(right, mid + (size%2));
	
	return merge(left,right);

}

