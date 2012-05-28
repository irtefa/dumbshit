EXENAME = mp3test

COMPILER = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++

MAIN_OBJS = main.o easypng.o blockpng.o
MAIN_DEPS = list.h list.cpp list_given.h list_given.cpp easypng.o blockpng.o main.cpp

EPNG_DEPS = easypng.h easypng.cpp
BPNG_DEPS = easypng.o blockpng.h blockpng.cpp

CODE_CLN = *.o $(EXENAME)

IMAG_CLN = waterfall*.png unshuffled*.png reverse*.png merge*.png split*.png

all: $(EXENAME)

$(EXENAME) : main.o
	$(LINKER) $(MAIN_OBJS) -lpng -o $(EXENAME)

main.o : $(MAIN_DEPS)
	$(COMPILER) $(COMPILER_OPTS) main.cpp

easypng.o : $(EPNG_DEPS)
	$(COMPILER) $(COMPILER_OPTS) easypng.cpp

blockpng.o : $(BPNG_DEPS)
	$(COMPILER) $(COMPILER_OPTS) blockpng.cpp

clean:
	-rm -f $(CODE_CLN) $(IMAG_CLN)
