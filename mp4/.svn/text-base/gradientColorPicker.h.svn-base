#ifndef GRADIENTCOLORPICKER_H
#define GRADIENTCOLORPICKER_H

#include"colorPicker.h"
#include<math.h>
#include<iostream>

class gradientColorPicker : public colorPicker{
  public:
    gradientColorPicker(RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, int centerX, int centerY);
    virtual RGBAPixel operator()(int x, int y);
  private:
	RGBAPixel fColor1;
	RGBAPixel fColor2;
	int memrad;
	int cX;
	int cY;
};

#endif
