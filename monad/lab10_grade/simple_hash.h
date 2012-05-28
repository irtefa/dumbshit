/*
   String Hash Functor (Lab 10)
   Created by Bill Bindi for CS225, Spring 2011
   Uses the Bernstein Hash
*/

#ifndef _SIMPLE_HASH_H_
#define _SIMPLE_HASH_H_
#include <string>
using std::string;

#include "hash.h"

class SimpleHash : public Hash<string> {
    public:
        virtual unsigned int operator()( string const & key, int size );
};
#endif

