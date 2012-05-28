#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include <string>
#include <iostream>
#include <sstream>
#include "image.h"
#include "easypng.h"

class Scene {

public:
	//constructors
	Scene(int max); 
	Scene(Scene const & source); 									// copy constructor
	~Scene();														// destructor
	Scene const & operator=(Scene const & source);					// assignment operator						
	//methods
	void addpicture(const char* FileName, int index, int x, int y); // add a picture to the scene
	void changemaxlayers(int newmax);								// mods the size of the array of image pointers without changing their indices
	void changelayer(int index, int newindex);						// moves an Image from location index to newindex
	void translate(int index, int xcoord, int ycoord);				// changes the x and y coords of teh Image in layer index
	void deletepicture(int index);									// deletes the Image at the given index
	Image* getpicture(int index) const;								// returns a pointer to the Image at the specified index
	Image drawscene() const;										// draws the whole scene on one image and returns that image by value
	
private:
	Image ** images; 												// array of image pointers
	int * xIndex;													// index of x
	int * yIndex;													// likewise
	int maxCapacity;												// the argument of the Scene constructor	
};
#endif // end of header file
