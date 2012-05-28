# When compiled with g++, the Intel tools show incorrect data races, so we are compiling with icc
# run "source /software/intel-composer-2011u5-x86_64/bin/compilervars.sh intel64" to set up compiler variables

EXAMPLENAME = example
LABNAME = lab05

COMPILER = icc -openmp 
COMPILER_OPTS = -c -g -O0 -Werror-all
LINKER = icc -openmp -lpng

MAIN_OBJS = main.o easypng.o
EXAMPLE_OBJS = example.o

MAIN_DEPS = easypng.o main.cpp
EPNG_DEPS = easypng.h easypng.cpp
EXAMPLE_DEPS = example.cpp

all: $(LABNAME) $(EXAMPLENAME)

$(LABNAME) : main.o
	$(LINKER) $(MAIN_OBJS) -o $(LABNAME)

$(EXAMPLENAME) : example.o
	$(LINKER) $(EXAMPLE_OBJS) -o $(EXAMPLENAME)

main.o : $(MAIN_DEPS)
	$(COMPILER) $(COMPILER_OPTS) main.cpp

example.o : $(EXAMPLE_DEPS)
	$(COMPILER) $(COMPILER_OPTS) example.cpp

easypng.o : $(EPNG_DEPS)
	$(COMPILER) $(COMPILER_OPTS) easypng.cpp

clean:
	-rm -f *.o $(LABNAME) $(EXAMPLENAME)
