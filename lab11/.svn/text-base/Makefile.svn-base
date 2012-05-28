CXX = g++
CXXFLAGS = -g -O0 -Wall -fopenmp
LFLAGS = -lpng -fopenmp -g -O0 -Wall

MIN = min
GENFILE = genfile
COUNTER = counter
HISTOGRAM = histogram

EXES = $(MIN) $(GENFILE) $(COUNTER) $(HISTOGRAM)

all: $(EXES)

$(MIN) : min.o
	$(CXX) $(LFLAGS) -o $(MIN) min.o

$(GENFILE) : genfile.o
	$(CXX) $(LFLAGS) -o $(GENFILE) genfile.o

$(COUNTER) : counter.o pnganalysis.o easypng.o tolerance_selector.o exact_selector.o
	$(CXX) $(LFLAGS) -o $(COUNTER) counter.o pnganalysis.o easypng.o tolerance_selector.o exact_selector.o

$(HISTOGRAM) : histogram.o pnganalysis.o easypng.o tolerance_selector.o exact_selector.o
	$(CXX) $(LFLAGS) -o $(HISTOGRAM) histogram.o pnganalysis.o easypng.o tolerance_selector.o exact_selector.o

easypng.o : easypng.h
	$(CXX) $(CXXFLAGS) -c easypng.cpp -o easypng.o

min.o : min.cpp findmin.h findmin.cpp
	$(CXX) $(CXXFLAGS) -c min.cpp -o min.o

genfile.o : genfile.cpp
	$(CXX) $(CXXFLAGS) -c genfile.cpp -o genfile.o

exact_selector.o : exact_selector.h selector.h exact_selector.cpp
	$(CXX) $(CXXFLAGS) -c exact_selector.cpp -o exact_selector.o

tolerance_selector.o : tolerance_selector.h selector.h tolerance_selector.cpp
	$(CXX) $(CXXFLAGS) -c tolerance_selector.cpp -o tolerance_selector.o

counter.o : pnganalysis.o counter.cpp
	$(CXX) $(CXXFLAGS) -c counter.cpp -o counter.o

pnganalysis.o : pnganalysis.h pnganalysis.cpp easypng.h selector.h compare.h pixel_hash.h
	$(CXX) $(CXXFLAGS) -c pnganalysis.cpp -o pnganalysis.o

histogram.o : pnganalysis.o histogram.cpp
	$(CXX) $(CXXFLAGS) -c histogram.cpp -o histogram.o

tidy:
	-rm -rf parallel serial *.png

clean: tidy
	-rm -rf *.o $(EXES)
