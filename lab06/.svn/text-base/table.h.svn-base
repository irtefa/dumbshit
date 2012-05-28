#ifndef _TABLE_H_
#define _TABLE_H_

#include <iostream>
#include <iomanip>
#include <omp.h>

using std::cout;
using std::endl;

namespace MultTable
{
    /**
     * Find all products of an m x n multiplication table and prints
     *  them out.
     *  @param table - a 2D int array where the result is stored
     *  @param width - the width of the multiplication table
     *  @param height - the height of the multiplication table
     *  @param print - whether to print the table
     */
    void findProductsParallel(int** table, int width, int height, bool print);
    
    /**
     * Find all products of an m x n multiplication table and prints
     *  them out.
     *  @param table - a 2D int array where the result is stored
     *  @param width - the width of the multiplication table
     *  @param height - the height of the multiplication table
     *  @param print - whether to print the table
     */
    void findProductsSerial(int** table, int width, int height, bool print);

    /**
     * Makes sure the multiplication table has the correct value in each cell.
     *  @param table - a 2D int array where the result is stored
     *  @param width - the width of the multiplication table
     *  @param height - the height of the multiplication table
     *  @return - whether the table is correct or not
     */
    bool checkTable(int** table, int width, int height);
}

#endif
