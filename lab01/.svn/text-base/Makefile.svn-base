EXE = lab01
OBJS = main.o easypng.o

COMPILER = g++
COMPILER_OPTS = -c -g -O0 -Wall -Werror
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

main.o : main.cpp easypng.h
	$(COMPILER) $(COMPILER_OPTS) main.cpp

easypng.o : easypng.cpp easypng.h
	$(COMPILER) $(COMPILER_OPTS) easypng.cpp

clean :
	-rm -f *.o lab01
