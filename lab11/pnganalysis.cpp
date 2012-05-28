/**
 * @file pnganalysis.cpp
 * Implementation for functions that perform analysis on PNG images.
 *
 * @author Chase Geigle
 * @date Spring 2012
 */
#include "pnganalysis.h"

/**
 * Finds the number of pixels in an image that satisfy a given
 * selector's criteria.
 * Graded! You will need to correctly parallelize this function to receive
 * credit.
 *
 * @param image  PNG to find pixel coordinates in
 * @param select Function object that takes in RGBAPixels and returns
 *				 a bool that determines whether the pixel should be
 *				 "selected" or not.
 * @return The number of pixels in the image for which the selector
 *         returns true.
 */
 int pnganalysis::num_selected( const PNG & image, selector & select ) {
	// Implement and parallelize this code!
	// Hint: use select( *image(i,j) ) to determine if a pixel is
	//       selected or not
	//
	// Hint2: You'll need a reduction!
 	int selected = 0;

	# pragma omp parallel for reduction(+:selected)
 	for(int i = 0; i < image.width(); i++)
 		for(int j = 0; j < image.height();j++)
 		{

 			if(select(*image(i,j)))
 			{
 				selected += 1;
 			}
 		}
 		return selected;
 	}

/**
 * Helper function that builds an unordered_map of color to frequency.
 * Graded! You need to modify this function such that it is correctly
 * parallelized to receive credit.
 *
 * @param image PNG to build the color frequency map from.
 * @return An unordered_map of colors to number of occurrences.
 */
 unordered_map<RGBAPixel, int> pnganalysis::frequency( const PNG & image ) {
 	
 	unordered_map<RGBAPixel, int> ret_freq;
 	
	#pragma omp parallel
 	{
 		unordered_map<RGBAPixel, int> loc_freq;
	
		#pragma omp for
 		for( int i = 0; i < image.width(); ++i ) 
 			for( int j = 0, height = image.height(); j < height; ++j )
 		{
 			++loc_freq[ *image(i,j) ];
 		}

 		unordered_map<RGBAPixel, int>::iterator curr;
 		unordered_map<RGBAPixel, int>::iterator end;
	
		#pragma omp critical
 		for( curr = loc_freq.begin(), end = loc_freq.end(); curr != end; ++curr ) 
 		{
 			ret_freq[curr->first] += curr->second;
 		}

 	}
 		
 	return ret_freq;
}

/**
 * Builds a color histogram for a given frequency map.
 * You do not have to modify this function!
 *
 * @param frequencies Map of pixels to their frequencies.
 * @param max_colors Maximum number of colors to display in the image.
 * @return A PNG representation of the histogram for the given image.
 */
 PNG pnganalysis::histogram( const unordered_map<RGBAPixel, int> & frequencies, size_t max_colors ) {
	// get the top colors
 	vector<RGBAPixel> colors = pnganalysis::top_colors( frequencies, max_colors );

	// determine number of colors we are going to display
 	size_t num_colors = colors.size();

	// bail if we don't have any colors
 	assert( num_colors > 0 );

	// determine histogram width
 	int out_width = bar_width * num_colors;

	// make output
 	PNG output( out_width, out_height );

	// iterate over the vector
 	vector<RGBAPixel>::iterator curr;
 	vector<RGBAPixel>::iterator end;
 	int start = 0;
 	int freq_base = frequencies.find(colors[0])->second;
 	for( curr = colors.begin(), end = colors.end(); curr != end; ++curr ) {
		// draw our bar for the bar graph
 		double ratio = (double)frequencies.find(*curr)->second / freq_base;
 		int bar_height = (int)(out_height * ratio);
 		for( int x = 0; x < bar_width; ++x ) {
 			for( int y = 0; y < bar_height; ++y) {
 				*output( start + x, out_height - 1 - y ) = *curr;
 			}
 		}
 		start += bar_width;
 	}
 	return output;
 }

/**
 * Helper function that creates a vector of the most frequently used colors
 * based off of a histogram.
 *
 * @param frequencies The map of color frequencies.
 * @param limit Number of colors to output.
 */
 vector<RGBAPixel> pnganalysis::top_colors( const unordered_map<RGBAPixel, int> & frequencies, size_t limit ) {
 	vector<RGBAPixel> colors;
	// iterate over the map
 	unordered_map<RGBAPixel, int>::const_iterator curr;
 	unordered_map<RGBAPixel, int>::const_iterator end;
 	for( curr = frequencies.begin(), end = frequencies.end(); curr != end; ++curr ) {
 		colors.push_back(curr->first);
 	}
 	compare<RGBAPixel, int> freq_compare(frequencies);
 	if( limit < colors.size() ) {
		// partition around the (limit-1)th element
 		std::nth_element(colors.begin(), colors.begin() + (limit - 1), colors.end(), freq_compare);
		// keep only things >= (limit-1)th element
 		colors.erase(colors.begin() + limit, colors.end());
 	}
	// sort the remaining colors
 	std::sort(colors.begin(), colors.end(), freq_compare);
 	return colors;
 }
