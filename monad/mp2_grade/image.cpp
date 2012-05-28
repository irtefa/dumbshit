#include "easypng.h"
#include "image.h"

using namespace std;

void Image::invertcolors()
{
	int myWidth = (*this).width();
	int myHeight = (*this).height();
	for(int i=0; i < myWidth; i++)
		for(int j=0; j < myHeight; j++)
	{
		int r1 = 255-((*this)(i,j)->red);
		int g1 = 255-((*this)(i,j)->green);
		int b1 = 255-((*this)(i,j)->blue);
		
		(*this)(i,j)->red   = r1;
		(*this)(i,j)->green = g1;
		(*this)(i,j)->blue  = b1;
	}
}

void Image::flipleft()
{
	int myWidth = (*this).width();
	int myHeight = (*this).height();

	for(int i=0; i < myWidth/2; i++)
	  for(int j=0; j < myHeight; j++)
	{
		int r,g,b;
		r = (*this)(i,j)->red;
		g = (*this)(i,j)->green;
		b = (*this)(i,j)->blue;

		int r2,g2,b2;

		r2 = (*this)(myWidth-i-1,j)->red;
		g2 = (*this)(myWidth-i-1,j)->green;
		b2 = (*this)(myWidth-i-1,j)->blue;

		(*this)(i,j)->red = r2;
		(*this)(i,j)->green = g2;
		(*this)(i,j)->blue = b2;

		(*this)(myWidth-i-1,j)->red = r;
		(*this)(myWidth-i-1,j)->green = g;
		(*this)(myWidth-i-1,j)->blue = b;
	}
}

void Image::adjustbrightness(int r, int g, int b)
{
	int myWidth = (*this).width();
	int myHeight = (*this).height();

	for(int i=0;i< myWidth;i++)
	  for(int j=0;j<myHeight;j++)
	{
			
		int varRed = (*this)(i,j)->red + r;
		if (varRed > 255)
			varRed = 255;
		else if (varRed < 0)
			varRed = 0;
		else
			varRed += 0;
		(*this)(i,j)->red = varRed;
		
		int varGreen = (*this)(i,j)->green + g;
		if (varGreen > 255)
			varGreen = 255;
		else if (varGreen < 0)
			varGreen = 0;
		else
			varGreen +=0;
		(*this)(i,j)->green = varGreen;
		int varBlue = (*this)(i,j)->blue + b;
		if (varBlue > 255)
			varBlue = 255;
		else if(varBlue < 0)
			varBlue = 0;
		else
			varBlue +=0;
		(*this)(i,j)->blue = varBlue;
	}
}

