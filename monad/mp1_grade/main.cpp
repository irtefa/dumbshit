#include <algorithm>
#include <iostream>
#include "easypng.h"

using namespace std;



int main()
{
  PNG image("in.png");
  
  int width = image.width();
  int height= image.height();
  
  PNG newImage(width,height);

  RGBAPixel *ptr1, *ptr2;

  for(int i=0; i < width;i++)
	for(int j=0; j < height; j++)
  {
  	ptr1 = image(i,j);
    ptr2 = newImage(width-1-i,height-1-j);

    *ptr2 = *ptr1;
  }
  
  newImage.writeToFile("out.png");
  
  return 0;
}
