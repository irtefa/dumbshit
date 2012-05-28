/**
 * @file compare.h
 * Definition and implementation for a comparison functor based on an
 * unordered_map.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
#ifndef _COMPARE_H_
#define _COMPARE_H_

#include <tr1/unordered_map>
#include "pixel_hash.h"

using std::tr1::unordered_map;

/**
 * Comparison functor for sorting based on an unordered_map.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
template <class K, class V>
class compare {
	public:
		compare( const unordered_map<K,V> & freq ) {
			_freq = freq;
		}

		bool operator()( const K & first, const K & second ) {
			return _freq[first] > _freq[second];
		}

	private:
		unordered_map<K,V> _freq;
};
#endif
