#ifndef FILLS_H
#define FILLS_H

//includes 
#include "easypng.h"
#include "stack.h"
#include "queue.h"
#include "solidColorPicker.h"
#include "gridColorPicker.h"
#include "gradientColorPicker.h"
#include "animation.h"


// High level wrappers for the driver functions
animation DFSfillSolid(PNG & img, int x, int y, RGBAPixel fillColor, int tolerance, int frameFreq);
animation DFSfillGrid(PNG & img, int x, int y, RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq);
animation DFSfillGradient(PNG & img, int x, int y, RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, int tolerance, int frameFreq);

animation BFSfillSolid(PNG & img, int x, int y, RGBAPixel fillColor, int tolerance, int frameFreq);
animation BFSfillGrid(PNG & img, int x, int y, RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq);
animation BFSfillGradient(PNG & img, int x, int y, RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, int tolerance, int frameFreq);


// Driver functions
animation DFSfill(PNG & img, int x, int y, colorPicker & fillColor, int tolerance, int frameFreq);
animation BFSfill(PNG & img, int x, int y, colorPicker & fillColor, int tolerance, int frameFreq);

#endif
