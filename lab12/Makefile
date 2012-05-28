EXENAME = testheap
COMPILER = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -g -O0 -Wfatal-errors -Werror $(WARNINGS)
OBJS = testheap.o

IS_LIBRT:=$(shell locate -l 1 -c librt.so)
ifeq ($(IS_LIBRT),0)
LIBRT=
else
LIBRT=-lrt
endif

$(EXENAME) : $(OBJS)
	$(COMPILER) $(LIBRT) -o $@ $^

testheap.o: testheap.cpp minheap.h minheap.cpp
	$(COMPILER) -c $(COMPILER_OPTS) testheap.cpp

clean:
	-rm -f *.o $(EXENAME)

