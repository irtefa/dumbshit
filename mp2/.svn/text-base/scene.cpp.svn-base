#include "scene.h"

using namespace std;

Scene::Scene(int max)
{
	images = new Image *[max];
	xIndex = new int[max];
	yIndex = new int[max];
	for(int i=0; i < max;i++)
	{
		images[i] = NULL;
		xIndex[i] = 0;
		yIndex[i] = 0;
	}
	maxCapacity = max;
}

Scene::~Scene()
{
	for(int i=0;i<maxCapacity;i++)
	{
		delete images[i];
	}
	delete [] images;
	delete [] xIndex;
	delete [] yIndex;
}

Scene::Scene(Scene const & source)
{
	maxCapacity = source.maxCapacity;
	images = new Image *[maxCapacity];
	xIndex = new int[maxCapacity];
	yIndex = new int[maxCapacity];
	
	for(int i=0; i < maxCapacity;i++)
	{
		images[i]  = new Image();
		if(source.images[i]!=NULL)
		{
			*images[i] = *(source.images[i]);
			xIndex[i]  = source.xIndex[i];
			yIndex[i]  = source.yIndex[i];
		}
		else
		{
			xIndex[i]=0;
			yIndex[i]=0;
		}
	}
}

Scene const & Scene::operator=(Scene const & source)
{
	if(this!=&source)
	{
		for(int i=0; i < maxCapacity;i++)
		{
			delete images[i];
			images[i] = NULL;
		}
		delete [] images;
		delete [] xIndex;
		delete [] yIndex;
		
		maxCapacity = source.maxCapacity;
		images = new Image *[maxCapacity];
		xIndex = new int[maxCapacity];
		yIndex = new int[maxCapacity];
		
		for(int i=0;i < maxCapacity;i++)
		{	
			images[i]  = new Image();
			if(source.images[i]!=NULL)
			{
				*images[i] = *(source.images[i]);
				xIndex[i]  = source.xIndex[i]; 
				yIndex[i]  = source.yIndex[i];
			}
		}
	}
	
	return *this;
}

void Scene::addpicture(const char* FileName, int index, int x, int y)
{
	if(index < maxCapacity && index >= 0)
	{
		Image* myImage = new Image();
		myImage->readFromFile(FileName);
		if(myImage !=NULL)
		{
			
			delete images[index];
			images[index] = new Image();
			*(images[index]) = *myImage;
			xIndex[index] = x;
			yIndex[index] = y;
		}
		delete myImage;
	}
	else
		cout << "index out of bounds" << endl;

}

void Scene::changemaxlayers(int newmax)
{
	bool invalid = false;
	for(int i=0; i < maxCapacity;i++)
	{
		if(images[i]!=NULL && i >= newmax)
			invalid = true;
	}
	if(!invalid)
	{
	 
	 	Image** newImages = new Image *[newmax];
		int * newX = new int[newmax];
	 	int * newY = new int[newmax];
	 	for(int i=0;i<newmax;i++)
	 	{
	 		newImages[i] = new Image();
	 		newImages[i] = NULL;
	 		if(images[i]!=NULL)
	 			*newImages[i] = *(images[i]);
	 		newX[i] = xIndex[i];
	 		newY[i] = yIndex[i];
	 		
	 		delete images[i];
	 	}
	 	
	 	delete [] images;
	 	delete [] xIndex;
	 	delete [] yIndex;
	 	
	 	images = new Image *[newmax];
	 	xIndex = new int[newmax];
	 	yIndex = new int[newmax];
	 	
	 	for(int i=0; i < newmax;i++)
	 	{
	 		images[i] = new Image();
	 		images[i] = NULL;
	 		if(newImages[i] != NULL)
	 			*(images[i]) = *(newImages[i]);
	 		xIndex[i] = newX[i];
	 		yIndex[i] = newY[i];
	 		delete newImages[i];
	 	}
	 	delete [] newImages;
	 	delete [] newX;
	 	delete [] newY;
	 }
	 	
	else
		cout << "invalid newmax" << endl;			
}

void Scene::changelayer(int index, int newindex)
{
	if(index==newindex)
		return;
		
	if(index < maxCapacity && newindex < maxCapacity && index >= 0 && maxCapacity > 0 && newindex >= 0)
	{
		if(images[newindex]!=NULL){
			delete images[newindex];
			images[newindex] = NULL;
		}
		 images[newindex] = new Image();	
		(*images[newindex])=(*images[index]);
		 delete images[index];
		 images[index] = NULL;	
		 xIndex[newindex] = xIndex[index];  // have to change the x,y coords as well
		 yIndex[newindex] = yIndex[index];
	 
	}
	
	else 
		cout << "invalid index" << endl;
}

void Scene::translate(int index, int xcoord, int ycoord)
{
	if(images[index]!=NULL && index >= 0 && index < maxCapacity)
	{
		xIndex[index] = xcoord;
		yIndex[index] = ycoord;
	}
	else
		cout << "invalid index" << endl;
}

void Scene::deletepicture(int index)
{
	if(images[index]!=NULL && index >= 0 && index < maxCapacity)
	{
		delete images[index];
		images[index] = NULL;
		xIndex[index] = 0;
		yIndex[index] = 0;
	}
}


Image* Scene::getpicture(int index) const
{
	if(images[index]!=NULL && index >= 0 && index < maxCapacity)
	{
		return (images[index]);
		
	}
	else
	{	
		cout << "invalid index" << endl;
		return NULL;
	}
}

Image Scene::drawscene() const
{
				//height
	int w= 0;				// highest x index
	int h= 0;				// highest y index
	
	for(int i=0;i<maxCapacity;i++)
	{
		if(images[i]!=NULL)
		{
		if((xIndex[i]+(*images[i]).width()) > w)
			w = xIndex[i] + (*images[i]).width();
		if((yIndex[i]+(*images[i]).height()) > h)
			h = yIndex[i] + (*images[i]).height();
		}
	}
	
	
	Image pic ;
	pic.resize(w,h);

	for(int a=0; a < maxCapacity;a++)
	{
		if(images[a]!=NULL)
		{
		
			
			int tempw = (*images[a]).width();
			int temph = (*images[a]).height();
			
		

			for(int i=0; i < tempw; i++)
				for(int j=0; j < temph; j++)
			{
				(pic)(i+xIndex[a],j+yIndex[a])->red 	= (*images[a])(i,j)->red;
				(pic)(i+xIndex[a],j+yIndex[a])->green 	= (*images[a])(i,j)->green;
				(pic)(i+xIndex[a],j+yIndex[a])->blue   = (*images[a])(i,j)->blue;
			}
		}
	}

	return pic; // it should return an Image value, not an image pointer!
}

















