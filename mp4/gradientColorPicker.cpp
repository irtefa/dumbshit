#include <stdlib.h>
#include "gradientColorPicker.h"

gradientColorPicker::gradientColorPicker(RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, int centerX, int centerY)
{
	fColor1 = fadeColor1;
	fColor2 = fadeColor2;
	memrad  = radius;
	cX = centerX;
	cY = centerY;
}

RGBAPixel gradientColorPicker::operator()(int x, int y)
{
	int d = abs(cX-x) + abs(cY-y);
	
	int red_value_1   = fColor1.red;
	int green_value_1 = fColor1.green;
	int blue_value_1  = fColor1.blue;

	int red_value_2   = fColor2.red;
	int green_value_2 = fColor2.green;
	int blue_value_2  = fColor2.blue;

    
	RGBAPixel retval;
	if(d < memrad){
	retval.red   = red_value_1 - floor((d*red_value_1)/memrad)+floor((d*red_value_2)/memrad);
	retval.green = green_value_1 - floor((d*green_value_1)/memrad)+floor((d*green_value_2)/memrad);
	retval.blue  = blue_value_1 - floor((d*blue_value_1)/memrad)+floor((d*blue_value_2)/memrad);
	}
	else
	{
		retval.red = red_value_2;
		retval.green = green_value_2;
		retval.blue  = blue_value_2;
	}
	return retval;	
}

