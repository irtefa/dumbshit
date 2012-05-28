/**
 * fills.cpp
 * CS 225 MP 4 Flood Fills
 *		   
 * Note: Make sure you return something from these functions before you run or you will have segfaults
 */
		   
#include "fills.h"

animation DFSfill(PNG& img, int x, int y, colorPicker & fillColor, int tolerance, int frameFreq)
{
  animation anim;
  int count = 0;
  if( x > img.width()-1 || y > img.height()-1)
	return anim;

  
  bool done[img.width()][img.height()];
  for(int i=0;i < img.width();i++)
	for(int j=0;j < img.height();j++)
  {
	 done[i][j] = false;
  }

  int origred = img(x,y)->red;
  int origgreen = img(x,y)->green;
  int origblue = img(x,y)->blue;
  int redsqr = 0;
  int grnsqr = 0;
  int blusqr = 0;

  int tolcheck = 0;

  Stack<int> rackx;
  Stack<int> racky;
  int a = 0;
  int b = 0;

  rackx.push(x);
  racky.push(y);
  //done[x][y]= true;
		
  while(!(rackx.isEmpty()))
  {
    a = rackx.pop();
	b = racky.pop();

	redsqr = (img(a,b)->red-origred) * (img(a,b)->red-origred);
	grnsqr = (img(a,b)->green-origgreen) * (img(a,b)->green-origgreen);
  	blusqr = (img(a,b)->blue-origblue) * (img(a,b)->blue-origblue);
   
    tolcheck = redsqr + grnsqr + blusqr;
	if((tolcheck <= tolerance && !done[a][b]))
	{
		*img(a,b) = fillColor(a,b); 
		count++;
	

	//done[a][b] = true;	

    	if(a+1 < img.width())
		{		
    		if(!done[a+1][b])
			{
				rackx.push(a+1);
				racky.push(b);
			//done(right[0],right[1]) = tru
			}
		}
		if(b+1 < img.height())
		{
			if(!done[a][b+1])
			{
				rackx.push(a);
				racky.push(b+1);
			}
		}

		if(a-1 > 0)
		{
			if(!done[a-1][b])
			{
				rackx.push(a-1);
				racky.push(b);
			}
		}
		if(b-1 > 0)
		{
			if(!done[a][b-1])
			{
				rackx.push(a);
				racky.push(b-1);
			}
		}
	}
	done[a][b] = true;
	
	if(frameFreq == count )
	{
		anim.addFrame(img);
		count = 0;
	}
  }
  return anim;
}
animation BFSfill(PNG& img, int x, int y, colorPicker & fillColor, int tolerance, int frameFreq)
{
	animation anim;
	 int count = 0;
  if( x > img.width()-1 || y > img.height()-1)
	return anim;

  
  bool done[img.width()][img.height()];
  for(int i=0;i < img.width();i++)
	for(int j=0;j < img.height();j++)
  {
	 done[i][j] = false;
  }

  int origred = img(x,y)->red;
  int origgreen = img(x,y)->green;
  int origblue = img(x,y)->blue;
  int redsqr = 0;
  int grnsqr = 0;
  int blusqr = 0;

  int tolcheck = 0;

  Queue<int> rackx;
  Queue<int> racky;
  int a = 0;
  int b = 0;

  rackx.enqueue(x);
  racky.enqueue(y);
  //done[x][y]= true;
		
  while(!(rackx.isEmpty()))
  {
    a = rackx.dequeue();
	b = racky.dequeue();

	redsqr = (img(a,b)->red-origred) * (img(a,b)->red-origred);
	grnsqr = (img(a,b)->green-origgreen) * (img(a,b)->green-origgreen);
  	blusqr = (img(a,b)->blue-origblue) * (img(a,b)->blue-origblue);
   
    tolcheck = redsqr + grnsqr + blusqr;
	if((tolcheck <= tolerance && !done[a][b]))
	{
		*img(a,b) = fillColor(a,b); 
		count++;
	

	//done[a][b] = true;	

    	if(a+1 < img.width())
		{		
    		if(!done[a+1][b])
			{
				rackx.enqueue(a+1);
				racky.enqueue(b);
			//done(right[0],right[1]) = tru
			}
		}
		if(b+1 < img.height())
		{
			if(!done[a][b+1])
			{
				rackx.enqueue(a);
				racky.enqueue(b+1);
			}
		}

		if(a-1 > 0)
		{
			if(!done[a-1][b])
			{
				rackx.enqueue(a-1);
				racky.enqueue(b);
			}
		}
		if(b-1 > 0)
		{
			if(!done[a][b-1])
			{
				rackx.enqueue(a);
				racky.enqueue(b-1);
			}
		}
	}
	done[a][b] = true;
	
	if(frameFreq <= count )
	{
		anim.addFrame(img);
		count = 0;
	}
  }
  return anim;
}


animation DFSfillSolid(PNG& img, int x, int y, RGBAPixel fillColor, int tolerance, int frameFreq)
{
	animation anim;
	solidColorPicker var = solidColorPicker(fillColor);
	anim = DFSfill(img,x,y,var,tolerance,frameFreq);
	//anim.write("dfsSolidTest.gif");
	return anim; // Your code here
}

animation DFSfillGrid(PNG& img, int x, int y, RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq)
{
	animation anim;
	gridColorPicker var = gridColorPicker(gridColor,gridSpacing);
	anim = DFSfill(img,x,y,var,tolerance,frameFreq);
	//anim.write("dfsGridTest.gif");
	return anim; // Your code here
}

animation DFSfillGradient(PNG& img, int x, int y, RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, int tolerance, int frameFreq)
{
	animation anim;
	gradientColorPicker var = gradientColorPicker(fadeColor1,fadeColor2,radius,x,y);
	anim = DFSfill(img,x,y,var,tolerance,frameFreq);
	//anim.write("dfsGradientTest.gif");
	return anim; // Your code here
}

animation BFSfillSolid(PNG& img, int x, int y, RGBAPixel fillColor, int tolerance, int frameFreq)
{
	animation anim;
	solidColorPicker var = solidColorPicker(fillColor);
	anim = BFSfill(img,x,y,var,tolerance,frameFreq);
	//anim.write("bfsSolidTest.gif");
	return anim; // Your code here
}

animation BFSfillGrid(PNG& img, int x, int y, RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq)
{
	animation anim;
	gridColorPicker var = gridColorPicker(gridColor, gridSpacing);
	anim = BFSfill(img,x,y,var,tolerance,frameFreq);
	//anim.write("bfsGridTest.gif");
	return anim; // Your code here
}

animation BFSfillGradient(PNG& img, int x, int y, RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, int tolerance, int frameFreq)
{
	animation anim;
	gradientColorPicker var = gradientColorPicker(fadeColor1,fadeColor2,radius,x,y);
	anim = BFSfill(img,x,y,var,tolerance,frameFreq);
	//anim.write("bfsGradientTest.gif");
	return anim; // Your code here
}
