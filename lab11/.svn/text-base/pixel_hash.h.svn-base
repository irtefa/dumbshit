#ifndef _PIXEL_HASH_H_
#define _PIXEL_HASH_H_

#include <tr1/unordered_map>

#include "easypng.h"

/**
 * @file pixel_hash.h
 * Definition and implementation of a hashing function for RGBAPixels to
 * allow use of unordered_map.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
namespace std {
	namespace tr1 {
		template <>
		struct hash<RGBAPixel> {
			size_t operator()( const RGBAPixel & pixel ) const {
				return ((size_t)pixel.red << 16) + ((size_t)pixel.green << 8) + (size_t)pixel.blue;
			}
		};
	}
}
#endif
