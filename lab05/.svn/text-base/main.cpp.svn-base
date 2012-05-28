/*
   Parallel Lab 01
   Written for CS 225 Spring 2012 by Sean Massung 
*/

#include <iostream>
#include <omp.h>
#include <vector>
#include <string>
#include "easypng.h"

using std::cout;
using std::endl;
using std::vector;

#define NUMARGS 3

enum Color { RED, GREEN, BLUE };

/**
 * @param source - the original PNG
 * @return - a copy of the parameter that has been flipped over the vertical
 * axis
 */
PNG verticalFlip(const PNG & source){

    int w = source.width(), h = source.height();
    PNG output(w, h);

    // insert your code to flip the image here
    // (shouldn't be more than two for loops)
    #pragma omp parallel for
    for (int i=0; i < w/2;i++)
    	for(int j=0; j < h; j++)
    {
    	//int r,g,b;
		output(w-i-1,j)->red = source(i,j)->red;
		output(w-i-1,j)->green = source(i,j)->green;
		output(w-i-1,j)->blue = source(i,j)->blue;

		//int r2,g2,b2;

		output(i,j)->red = source(w-i-1,j)->red;
		output(i,j)->green = source(w-i-1,j)->green;
		output(i,j)->blue = source(w-i-1,j)->blue;

		/*output(i,j)->red = r2;
		output(i,j)->green = g2;
		output(i,j)->blue = b2;

		output(w-i-1,j)->red = r;
		output(w-i-1,j)->green = g;
		output(w-i-1,j)->blue = b;*/
	}

    return output;
}

/**
 * @param source - the original PNG
 * @param color - if 'R', remove red component
 *                if 'G', remove green component
 *                if 'B', remove blue component
 *                otherwise, do nothing
 * @return - a PNG object with an RGB component taken out
 *              of each pixel (if color parameter is valid)
 */
PNG removeColor(const PNG & source, const Color & color){

    int w = source.width(), h = source.height();
    PNG output(w, h);
	
	#pragma omp parallel for
    for(int i = 0; i < w; ++i){
        for(int j = 0; j < h; ++j){
            *output(i, j) = *source(i, j);
            switch(color){
                case RED:
                     output(i,j)->red = 0;// clear red values in current output pixel
                    break;
                case GREEN:
                    output(i,j)->green = 0;// clear green values in current output pixel
                    break;
                case BLUE:
                    output(i,j)->blue = 0;// clear blue values in current output pixel
                    break;
            }
        }
    }

    return output;
}

/**
 * @param sourcePNGs - vector of PNGs to vertically flip
 * @return - a vector of processed PNGs
 */
vector<PNG> processVerticalFlip(const vector<PNG> & sourcePNGs){

    vector<PNG> processed;
    vector<PNG>::const_iterator iter;
    for(iter = sourcePNGs.begin(); iter != sourcePNGs.end(); ++iter){
        PNG current = verticalFlip(*iter);
        processed.push_back(current);
    }

    return processed;
}

/**
 * @param sourcePNGs - vector of PNGs to remove color from
 * @param color - for the removeColor() argument
 * @return - a vector of processed PNGs
 */
vector<PNG> processRemoveColor(const vector<PNG> & sourcePNGs, const Color & color){

    vector<PNG> processed;
    vector<PNG>::const_iterator iter;
    for(iter = sourcePNGs.begin(); iter != sourcePNGs.end(); ++iter){
        PNG current = removeColor(*iter, color);
        processed.push_back(current);
    }

    return processed;
}

int main(int argc, char* argv[]){

    if(argc != NUMARGS){
        cerr << "Please run as " + (string)argv[0] + " numThreads images/imagename.png" << endl;
        return 1;
    }

    // set the number of thread for the program to use (the first argument)
    omp_set_num_threads(atoi(argv[1]));
    
    string fileName(argv[2]);
    PNG img(fileName);
    vector<PNG> toProcess;
    toProcess.push_back(img);

    // Vertically flip
    // (parts in the left side of the image will be on the right and vice versa)
    vector<PNG> rotated = processVerticalFlip(toProcess);
    vector<PNG>::iterator iter;
    for(iter = rotated.begin(); iter != rotated.end(); ++iter){
       iter->writeToFile("flipped.png");
    }

    // Remove an RGB color component
    vector<PNG> nogreen = processRemoveColor(toProcess, GREEN);
    for(iter = nogreen.begin(); iter != nogreen.end(); ++iter){
       iter->writeToFile("nogreen.png");
    }

    // show number of total pixels processed
    int numProcessed = 0;
    for(iter = nogreen.begin(); iter != nogreen.end(); ++iter){
        numProcessed += iter->height() * iter->width();
    }

    cout << "Total processed pixels: " << numProcessed << endl;
}
