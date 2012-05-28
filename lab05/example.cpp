/*
   Parallelism Example - add two arrays together
   Written for CS 225 Spring 2012 by Sean Massung 
*/

#include <iostream>
#include <cmath>
#include <omp.h>
#include <cstdlib>
#include <string>

using namespace std;

#define RANDOM_SEED 42
#define DEFAULT_SIZE 10000000

/**
 * getRandomArray
 *
 * @param arraySize - the length of the array
 * @return - a pointer to the array. You must free it when done.
 */
double* getRandomArray(size_t arraySize){
    double* array = new double[arraySize];
    for(size_t i = 0; i < arraySize; ++i){
        array[i] = rand();
    }
    return array;
}

int main(int argc, char* argv[]){

    // determine array size
    size_t arraySize;
    if(argc > 2){
        cout << "Usage " + (string)argv[0] + " arraySize" << endl;
        return 1;
    } else if(argc == 1){
       arraySize = DEFAULT_SIZE; 
    } else {
        arraySize = atol(argv[1]);
    }

    // get two random arrays
    srand(RANDOM_SEED);
    double* one = getRandomArray(arraySize);
    double* two = getRandomArray(arraySize);

    // start timing
    double start = omp_get_wtime();

    // do an intensive operation
    #pragma omp parallel for
    for(size_t i = 0; i < arraySize; ++i){
        double a = one[i] + floor(two[i]*0.1);
        double b = log10(pow(10, 32));
        double c = (size_t)one[i] >> (size_t)b;
        double d = (size_t)two[i] ^ (size_t)one[i] << (size_t)b;
        one[i] = c + b*sqrt(sqrt(b*a)) + log(log(a*b*a*b)) + d;
    }

    // end timing
    double end = omp_get_wtime();
    
    // print result
    for(size_t i = 0; i < arraySize; ++i){
        cout << one[i] << " ";
    }
    cout << endl;
    cerr << "Calculation took " << end - start << " seconds." << endl;

    // clean up
    delete [] one;
    delete [] two;
}
