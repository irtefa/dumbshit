/**
 * maptiles.cpp
 *	 			
 * mapTiles() function
 *	 			
 * Author: Jack Toole
 *	 			
 * Developed for CS225 PhotoMosaic MP
 * Fall 2011
 */
	 			
#include "maptiles.h"
#include <iostream>
#include <map>

using namespace std;

/*
 * Map the image tiles into a mosaic canvas which closely
 * matches the input image.
 *	 			
 * @param theSource The input image to construct a photomosaic of
 * @param theTiles The tiles image to use in the mosaic
 */
MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
	
	int rows = theSource.getRows();
	int cols = theSource.getColumns();

	if(rows==0 || cols==0)
	{
		return NULL;
	}

	MosaicCanvas * retval = new MosaicCanvas(rows,cols);

	// make the hashmap for TileImages, keys are the points

	map<Point<3>,TileImage> hashMap;
	//map<Point<3>,TileImage> iterator it;
	
	// passing in the tile points
	vector<Point<3> > theTilePoints;

	// fill theTilePoints with the theTiles indices
	for(unsigned int i = 0; i < theTiles.size();i++)
	{
		RGBAPixel tileavg   = theTiles[i].getAverageColor();

		Point<3> p(tileavg.red, tileavg.green, tileavg.blue);

		theTilePoints.push_back(p);


		pair<Point<3>,TileImage> myPair;

		myPair.first  = theTilePoints[i];
		myPair.second = theTiles[i];
		hashMap.insert(myPair);

	}

	if(theTilePoints.empty())
	{
		return NULL;
	}

	// build the tree
	KDTree<3> kdtree(theTilePoints);

	// loop through the source image's rectangle
	for(int j = 0; j < cols; j++)
		for(int i = 0; i < rows; i++)
	{
		RGBAPixel regionColor = theSource.getRegionColor(i,j);


		int r = regionColor.red;
		int g = regionColor.green;
		int b = regionColor.blue;

		Point<3> search(r,g,b);

		Point<3> num = kdtree.findNearestNeighbor(search);

		//find the tile
		TileImage temp = hashMap.find(num)->second;
		retval->setTile(i,j,temp);
	}

	return retval; 
}



