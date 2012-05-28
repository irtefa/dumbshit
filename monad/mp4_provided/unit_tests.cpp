// CS 225 MP 4 Unit Tests

#include <cmath>
#include <limits.h>
#include <sys/stat.h>

#include "proxy.h"
#include "util.h"

#include "stack.h"
#include "queue.h"

#include "animation.h"
#include "colorPicker.h"
#include "fills.h"
#include "gradientColorPicker.h"
#include "gridColorPicker.h"
#include "solidColorPicker.h"

#include "rainbowColorPicker.h" 

using namespace std;
using namespace util;

#define FUNCTORTESTHEIGHT 60
#define FUNCTORTESTWIDTH 60
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 35
#define FUNCTORTESTGRIDSPACING 8

#define SOLIDX 43
#define SOLIDY 15
#define SOLIDTOLERANCE 700
#define SOLIDTESTIMAGE "originals/solidTest.png"
#define SOLIDFRAMEFREQ 130

#define GRIDX 40
#define GRIDY 25
#define GRIDTOLERANCE 7000
#define GRIDTESTIMAGE "originals/gridTest.png"
#define GRIDFRAMEFREQ 20
#define GRIDGRIDSPACING 3

#define GRADIENTX 80
#define GRADIENTY 80
#define GRADIENTTOLERANCE 8500
#define GRADIENTTESTIMAGE "originals/gradientTest.png"
#define GRADIENTFRAMEFREQ 150 
#define GRADIENTRADIUS 25

#define PACMANTESTIMAGE "originals/pacMan.png"

#define IMAGETOLERANCE 5


#define ASSERT_PNG_EQUALS_WITH_TOLERANCE( a, solnfile, tolerance) \
	do { \
		PNG frame=a;\
		PNG soln_frame;\
		soln_frame.readFromFile((solnfile).c_str());\
		if(soln_frame.width() != frame.width() || soln_frame.height() != frame.height()) \
			FAIL("Incorrect Image Size");\
		for(int x = 0; x < frame.width(); x++)\
		for(int y = 0; y < frame.height(); y++) {\
			if(abs(frame(x,y)->red-soln_frame(x,y)->red) > tolerance ||\
					abs(frame(x,y)->green-soln_frame(x,y)->green) > tolerance ||\
					abs(frame(x,y)->blue-soln_frame(x,y)->blue) > tolerance) {\
				cout << "Images differ too much at point (" << x << ", " << y << ")." << endl;\
				cout << "soln: R=" << (int)soln_frame(x,y)->red << " G=" << (int)soln_frame(x,y)->green << " B=" << (int)soln_frame(x,y)->blue << endl;\
				cout << "yours: R=" << (int)frame(x,y)->red << " G=" << (int)frame(x,y)->green << " B=" << (int)frame(x,y)->blue << endl;\
				FAIL("Images differ too much at point (" + to_string(x) + ", " + to_string(y) + ")");\
			}\
		} \
	} while (0)








/* MP3.1 tests - stacks and queues */

UNIT_TEST(testStack, 1, 1, 1000)
{
	Stack<int> intStack;

	// build stack
	for(int i = 1; i <= 10; i++)
		intStack.push(i);

	// test values
	int counter = 10;
	int peekValue = intStack.peek(); // in case their peek pops off the value
	
	if( peekValue != 10 )
		FAIL("Stack peek not correct. Expected 10, got " + to_string(peekValue));

	while( !intStack.isEmpty() )
	{
		ASSERT( counter == intStack.pop() );
		counter--;
	}
	if( counter != 0 )
		FAIL("Did not go through the whole stack");
}

UNIT_TEST(testQueue, 1, 1, 1000)
{
	Queue<int> intQueue;

	// build queue
	for(int i = 1; i <= 10; i++)
		intQueue.enqueue(i);

	// test values
	int counter = 1;
	int peekValue = intQueue.peek(); // in case their peek dequeues the value

	if( peekValue != 1)
		FAIL("Queue peek not correct. Expected 1, got " + to_string(peekValue));

	while( !intQueue.isEmpty() )
	{
		ASSERT( counter == intQueue.dequeue() );
		counter++;
	}
	if( counter != 11 )
		FAIL("Did not go through the whole queue");
}


/* MP3.2 tests - BFS and DFS */

// helper for testing colorPickers
PNG testColorPicker(colorPicker & picker) {
	PNG img;
	img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);

	for(int x = 0; x < FUNCTORTESTWIDTH; x++)
		for(int y = 0; y < FUNCTORTESTHEIGHT; y++)
			*img(x, y) = picker(x, y);

	return img;
}

UNIT_TEST(testSolidColorPicker, 1, 1, 1000)
{
	RGBAPixel px;
	px.red = 255;
	px.blue = px.green = 100;
	solidColorPicker solidPicker(px);

	PNG solidResult = testColorPicker(solidPicker);
	PNG solidExpected("./soln_images/solidColorPickerTest.png");
	ASSERT(solidResult == solidExpected);
}

UNIT_TEST(testGradientColorPicker, 1, 1, 1000)
{
	RGBAPixel px1, px2;
	px1.red = 255;
	px1.blue = px1.green = 100;
	px2.blue = 255;
	px2.green = px2.red = 10;
	gradientColorPicker gradientPicker(px1, px2, FUNCTORTESTRADIUS, FUNCTORTESTX, FUNCTORTESTY);

	PNG gradientResult = testColorPicker(gradientPicker);
	PNG gradientExpected("./soln_images/gradientColorPickerTest.png");
	ASSERT(gradientResult == gradientExpected);
}

UNIT_TEST(testGridColorPicker, 1, 1, 1000)
{
	RGBAPixel px1;
	px1.green = 255;
	px1.blue = px1.red = 110;
	gridColorPicker gridPicker(px1, FUNCTORTESTGRIDSPACING);

	PNG gridResult = testColorPicker(gridPicker);
	PNG gridExpected("./soln_images/gridColorPickerTest.png");
	ASSERT(gridResult == gridExpected);
}


UNIT_TEST(testSolidDFS, 1, 1, 10000)
{
	PNG img;
	img.readFromFile(SOLIDTESTIMAGE);
	RGBAPixel px;
	px.red = 70;
	px.green = 50;
	px.blue = 13;

	animation anim = DFSfillSolid(img, SOLIDX, SOLIDY, px, SOLIDTOLERANCE, SOLIDFRAMEFREQ);

	for(int i = 0; i < anim.size(); i++) {
		ASSERT_PNG_EQUALS_WITH_TOLERANCE(anim.frame(i), "soln_frames/dfsSolidTest" + to_string(i) + ".png", IMAGETOLERANCE);
	}
}

UNIT_TEST(testSolidBFS, 1, 1, 10000)
{
	PNG img;
	img.readFromFile(SOLIDTESTIMAGE);
	RGBAPixel px;
	px.red = 70;
	px.green = 50;
	px.blue = 13;

	animation anim = BFSfillSolid(img, SOLIDX, SOLIDY, px, SOLIDTOLERANCE, SOLIDFRAMEFREQ);

	for(int i = 0; i < anim.size(); i++) {
		ASSERT_PNG_EQUALS_WITH_TOLERANCE(anim.frame(i), "soln_frames/bfsSolidTest" + to_string(i) + ".png", IMAGETOLERANCE);
	}
}

UNIT_TEST(testGradientDFS, 1, 1, 10000)
{
	PNG img;
	img.readFromFile(GRADIENTTESTIMAGE);
	RGBAPixel px;
	px.red = px.blue = 0;
	px.green = 25;
	RGBAPixel px2;
	px2.red = px2.blue = 200;
	px2.green = 25;

	animation anim = DFSfillGradient(img, GRADIENTX, GRADIENTY, px, px2, GRADIENTRADIUS, GRADIENTTOLERANCE, GRADIENTFRAMEFREQ);

	for(int i = 0; i < anim.size(); i++) {
		ASSERT_PNG_EQUALS_WITH_TOLERANCE(anim.frame(i), "soln_frames/dfsGradientTest" + to_string(i) + ".png", IMAGETOLERANCE);
	}
}

UNIT_TEST(testGradientBFS, 1, 1, 10000)
{
	PNG img;
	img.readFromFile(GRADIENTTESTIMAGE);
	RGBAPixel px;
	px.red = px.blue = 0;
	px.green = 25;
	RGBAPixel px2;
	px2.red = px2.blue = 200;
	px2.green = 25;

	animation anim = BFSfillGradient(img, GRADIENTX, GRADIENTY, px, px2, GRADIENTRADIUS, GRADIENTTOLERANCE, GRADIENTFRAMEFREQ);

	for(int i = 0; i < anim.size(); i++) {
		ASSERT_PNG_EQUALS_WITH_TOLERANCE(anim.frame(i), "soln_frames/bfsGradientTest" + to_string(i) + ".png", IMAGETOLERANCE);
	}
}

UNIT_TEST(testGridDFS, 1, 1, 10000)
{
	PNG img;
	img.readFromFile(GRIDTESTIMAGE);
	RGBAPixel px;
	px.red = px.blue = 70;
	px.green = 25;

	animation anim = DFSfillGrid(img, GRIDX, GRIDY, px, GRIDGRIDSPACING, GRIDTOLERANCE, GRIDFRAMEFREQ);

	for(int i = 0; i < anim.size(); i++) {
		ASSERT_PNG_EQUALS_WITH_TOLERANCE(anim.frame(i), "soln_frames/dfsGridTest" + to_string(i) + ".png", IMAGETOLERANCE);
	}
}

UNIT_TEST(testGridBFS, 1, 1, 10000)
{
	PNG img;
	img.readFromFile(GRIDTESTIMAGE);
	RGBAPixel px;
	px.red = px.blue = 70;
	px.green = 25;

	animation anim = BFSfillGrid(img, GRIDX, GRIDY, px, GRIDGRIDSPACING, GRIDTOLERANCE, GRIDFRAMEFREQ);

	for(int i = 0; i < anim.size(); i++) {
		ASSERT_PNG_EQUALS_WITH_TOLERANCE(anim.frame(i), "soln_frames/bfsGridTest" + to_string(i) + ".png", IMAGETOLERANCE);
	}
}


// helper for antiPacMan tests
PNG makeAntiPacMan()
{
	PNG antiImg;
	antiImg.readFromFile(PACMANTESTIMAGE);
	RGBAPixel black;
	black.red = black.green = black.blue = 0;
	RGBAPixel grey;
	grey.red = grey.green = grey.blue = 1;
	BFSfillSolid(antiImg, 10, 10, grey, 8000, INT_MAX);
	BFSfillSolid(antiImg, antiImg.width()/2, antiImg.height()/2, black, 8000, INT_MAX);
	return antiImg;
}


UNIT_TEST(testPacManDFS, 1, 1, 10000)
{
	PNG result;
	result.readFromFile(PACMANTESTIMAGE);
	rainbowColorPicker DFSfiller(1.0/1000.0);
	
	animation anim = DFSfill(result, result.width()/2, result.height()/2, DFSfiller, 8000, INT_MAX);

	PNG expected("soln_images/pacManDFS.png");
	ASSERT( result == expected );
}

UNIT_TEST(testPacManBFS, 1, 1, 10000)
{
	PNG result;
	result.readFromFile(PACMANTESTIMAGE);
	rainbowColorPicker BFSfiller(1.0/1000.0);
	
	animation anim = BFSfill(result, result.width()/2, result.height()/2, BFSfiller, 8000, INT_MAX);

	PNG expected("soln_images/pacManBFS.png");
	ASSERT( result == expected );
}

UNIT_TEST(testAntiPacManDFS, 1, 1, 10000)
{
	PNG img = makeAntiPacMan();
	rainbowColorPicker aDFSfiller(1.0/1000.0);

	animation anim = DFSfill(img, 20, 20, aDFSfiller, 0, 2000);

	for(int i = 0; i < anim.size(); i++) {
		ASSERT_PNG_EQUALS_WITH_TOLERANCE(anim.frame(i), "soln_frames/antiPacManDFS" + to_string(i) + ".png", IMAGETOLERANCE);
	}
}

UNIT_TEST(testAntiPacManBFS, 1, 1, 10000)
{
	PNG img = makeAntiPacMan();
	rainbowColorPicker aBFSfiller(1.0/1000.0);

	animation anim = BFSfill(img, 20, 20, aBFSfiller, 0, 2000);

	for(int i = 0; i < anim.size(); i++) {
		ASSERT_PNG_EQUALS_WITH_TOLERANCE(anim.frame(i), "soln_frames/antiPacManBFS" + to_string(i) + ".png", IMAGETOLERANCE);
	}
}

