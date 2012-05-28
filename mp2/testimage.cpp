/**********************************************************
 * testimage.cpp -- part of CS225 MP2
 *
 * This file performs some basic tests of the Image class.
 * It is not intended to catch every possible error.You may 
 * modifty this or write your own testimage.cpp to perform 
 * additional tests.
 *
 *   Author: Jonathan Ray
 *   Date: 02 Feb 2007
 */

#include "image.h"
#include "easypng.h"



int main()
{
	Image* myImage = new Image();
	bool b = myImage->readFromFile("in_01.png");
	myImage->invertcolors();
	b = myImage->writeToFile("inverted.png");
	
	myImage->flipleft();
	b = myImage->writeToFile("flipped.png");

	
	myImage->adjustbrightness(20, 20, -40);
	b = myImage->writeToFile("brightened.png");

	delete myImage;
	
	return 0;
}

