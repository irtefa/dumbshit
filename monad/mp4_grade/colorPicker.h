#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "easypng.h"

class colorPicker {
  public:
    virtual ~colorPicker() {};
    virtual RGBAPixel operator()(int x, int y) = 0;
};

#endif
