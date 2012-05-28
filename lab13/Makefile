CC = g++ -std=c++0x
CC_OPTS = -O0 -g -c
LINKER = g++ -std=c++0x

DEMO = graphdemo
DEMO_OBJS = graph.o demo.o

LAB14 = lab14
LAB14_OBJS = graph.o graph_tools.o dsets.o

DSETS = libdsets/dsets.h libdsets/dsets.cpp

all: $(DEMO) $(LAB14)

$(DEMO): $(DEMO_OBJS)
	$(LINKER) -o $(DEMO) $(DEMO_OBJS)
	
$(LAB14): $(LAB14_OBJS) tests.cpp
	$(LINKER) -o $(LAB14) tests.cpp $(LAB14_OBJS)
    
demo.o: demo.cpp
	$(CC) $(CC_OPTS) demo.cpp
	
graph.o: random.h random.cpp graph.h graph.cpp premade_graphs.h premade_graphs.cpp
	$(CC) $(CC_OPTS) graph.cpp
	
graph_tools.o: graph_tools.h graph_tools.cpp $(DSETS)
	$(CC) $(CC_OPTS) graph_tools.cpp
	
dsets.o: libdsets/dsets.cpp libdsets/dsets.h
	$(CC) $(CC_OPTS) libdsets/dsets.cpp
	
clean:
	-rm -f *.o $(DEMO) $(LAB14) libdsets/*.gch

tidy: clean
	-rm -f images/*.png

spotless: clean tidy
	-rm -rf doc
