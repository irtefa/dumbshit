/*
   Heap Testing Code (Lab 11)
   Created by Jack Toole for CS225, Fall 2011
    - Updated (Gnuplot) by Chase Geigle, Spring 2011
*/
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
#include <utility>
#include "minheap.h"
#include "random.h"

using namespace std;
using namespace util;

int main(int argc, const char ** argv)
{
    cout << endl;
    unsigned int seed = time(NULL) % 100;

    // Get random seed
    if (argc >= 2)
        seed = atoi(argv[1]);

    // Heap verification variables
    vector<int> myHeap;
	vector<int> unsortedArray;
    usrand(seed);

    int count    = 50;
    int inserts  = 0;
    int removals = 0;

    cout << "Testing heapifyDown..." << endl;
    cout << "Seed " << seed;

    // Verify the heap's correctness
    while (removals < count)
    {
        // Randomly choose insertion/removal
        if (myHeap.empty() || urand() % 2 != 0)
        {
			int val = urand() % 50;
            heapInsert(myHeap, val);
			unsortedArray.push_back(val);
            inserts++;
        }
        else
        {
            int myItem = removeMin(myHeap);
			
			vector<int>::iterator unsortedMinIndex = min_element(unsortedArray.begin(), unsortedArray.end());
			int unsortedItem = *unsortedMinIndex;
			unsortedArray.erase(unsortedMinIndex);

            removals++;

            // Dump failure information
            if (myItem != unsortedItem)
            {
                cout << endl << "Failed on " << removals << "th removal:"
                    " returned incorrect " << myItem << ", should have been " << unsortedItem << endl;

                cout << "Heap: ";
                print(myHeap);
                cout << endl << endl;

                return removals;
            }
        }
    }

    cout << endl << "heapifyDown passed" << endl << endl;

    // Verify buildheap
    cout << "Testing buildheap constructor..." << endl;
    vector<int> randoms;
    randoms.resize(100);
    for (unsigned int i = 0; i < randoms.size(); i++)
        randoms[i] = urand() % randoms.size();

    vector<int> fastHeap = randoms;
	buildHeap(fastHeap);
    sort(randoms.begin(), randoms.end());

    for (unsigned int i = 0; i < randoms.size(); i++)
    {
		int myItem = removeMin(fastHeap);
        if (randoms[i] != myItem)
        {
            cout << "buildHeap failed on " << i << "th removal. "
                "expected " << randoms[i] << ", but was " << myItem << endl;
            return i;
        }
    }

    cout << "buildHeap passed" << endl << endl;


    return 0;
}




typedef struct you_used_a_value_instead_of_an_index
{
    int a;
    you_used_a_value_instead_of_an_index()      { a = 0; }
    you_used_a_value_instead_of_an_index(int b) { a = b; }
    bool operator<(const you_used_a_value_instead_of_an_index & other) const
    { return a < other.a; }
} cTestStruct;
using namespace std::rel_ops;

void testCompileOnly()
{
    vector<cTestStruct> input;
    input.push_back(cTestStruct(1));
    input.push_back(cTestStruct(0));
    input.push_back(cTestStruct(2));
    vector<cTestStruct> testDouble;
	buildHeap(testDouble);
    removeMin(testDouble);
}
