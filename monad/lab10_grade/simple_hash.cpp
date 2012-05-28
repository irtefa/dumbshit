/*
   String Hash Functor (Lab 10)
   Created by Bill Bindi for CS225, Spring 2011
   Uses simplest hash possible
*/

#include "simple_hash.h"

unsigned int SimpleHash::operator()( string const & key, int size ) {
    int h = (int) key[0];
    return h % size;
}
