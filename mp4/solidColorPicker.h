#ifndef SOLIDCOLORPICKER_H
#define SOLIDCOLORPICKER_H

#include"colorPicker.h"

class solidColorPicker : public colorPicker{
  public:
    solidColorPicker(RGBAPixel fillColor);
    virtual RGBAPixel operator()(int x, int y);
  private:
	RGBAPixel color;
};

#endif
