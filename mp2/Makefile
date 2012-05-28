SCENEEXE = testscene
IMAGEEXE = testimage

SCENEOBJS = testscene.o image.o easypng.o scene.o
IMAGEOBJS = image.o easypng.o testimage.o 

COMPILER = g++
COMPILER_OPTS = -c -g -O0 -Wall
LINKER = g++
LINKER_OPTS = -lpng

all : $(SCENEEXE) $(IMAGEEXE)

$(SCENEEXE) : $(SCENEOBJS)
	$(LINKER) $(SCENEOBJS) $(LINKER_OPTS) -o $(SCENEEXE)

$(IMAGEEXE) : $(IMAGEOBJS)
	$(LINKER) $(IMAGEOBJS) $(LINKER_OPTS) -o $(IMAGEEXE)
	
testscene.o : testscene.cpp easypng.h image.h scene.h
	$(COMPILER) $(COMPILER_OPTS) testscene.cpp
	
testimage.o : testimage.cpp easypng.h image.h
	$(COMPILER) $(COMPILER_OPTS) testimage.cpp
		
easypng.o : easypng.cpp easypng.h
	$(COMPILER) $(COMPILER_OPTS) easypng.cpp

image.o : image.cpp image.h 
	$(COMPILER) $(COMPILER_OPTS) image.cpp
	
scene.o : scene.cpp scene.h 
	$(COMPILER) $(COMPILER_OPTS) scene.cpp	

clean : 
	-rm -f *.o $(SCENEEXE) $(IMAGEEXE)

