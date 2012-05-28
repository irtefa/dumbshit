#include "solidColorPicker.h"


solidColorPicker::solidColorPicker(RGBAPixel fillColor)
{
	color = fillColor;
}

RGBAPixel solidColorPicker::operator()(int x, int y)
{
	RGBAPixel retval = color;
	return retval;
}
