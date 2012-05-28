# When compiled with g++, the Intel tools show incorrect data races, so we are compiling with icc

EXENAME = lab06

COMPILER = icpc -openmp 
COMPILER_OPTS = -c -g -O0 # -Werror-all
LINKER = icpc -openmp -lpng

MAIN_OBJS = point.o easypng.o collage.o table.o flipper.o shifter.o animation.o main.o

all: $(EXENAME)

$(EXENAME) : $(MAIN_OBJS)
	$(LINKER) $(MAIN_OBJS) -o $(EXENAME)

main.o : easypng.o collage.o table.o main.cpp
	$(COMPILER) $(COMPILER_OPTS) main.cpp

table.o : table.h table.cpp
	$(COMPILER) $(COMPILER_OPTS) table.cpp

shifter.o : easypng.o animation.o shifter.h shifter.cpp
	$(COMPILER) $(COMPILER_OPTS) shifter.cpp

animation.o : animation.h animation.cpp
	$(COMPILER) $(COMPILER_OPTS) animation.cpp

flipper.o : flipper.h flipper.cpp
	$(COMPILER) $(COMPILER_OPTS) flipper.cpp

collage.o : point.o easypng.o collage.h collage.cpp
	$(COMPILER) $(COMPILER_OPTS) collage.cpp

easypng.o : easypng.h easypng.cpp
	$(COMPILER) $(COMPILER_OPTS) easypng.cpp

point.o : point.h point.cpp
	$(COMPILER) $(COMPILER_OPTS) point.cpp

clean:
	-rm -f *.o $(EXENAME)

tidy:
	-rm -rf frames/ *.o $(EXENAME) collage.png shifted.gif flipped.png 
