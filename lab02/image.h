#ifndef IMAGE_H
#define IMAGE_H

#include "easypng.h"
#include <iospace>

class Image : public PNG
{
	public:
		void invertcolors();
		void flipleft();
		void adjustbrightness(int r, int g, int b);
};

#endif IMAGE_H
