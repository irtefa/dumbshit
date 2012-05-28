EXENAME=testFills
OBJS=testFills.o animation.o fills.o easypng.o solidColorPicker.o gridColorPicker.o gradientColorPicker.o rainbowColorPicker.o

COMPILER = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
COMPILER_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)
LINKER = g++

all: $(EXENAME) testStackQueue

$(EXENAME): $(OBJS)
	$(LINKER) -lpng -o $(EXENAME) $(OBJS)

testStackQueue: testStackQueue.o
	$(LINKER) -o testStackQueue testStackQueue.o

testStackQueue.o: testStackQueue.cpp stack.h stack.cpp queue.h queue.cpp
	$(COMPILER) $(COMPILER_OPTS) testStackQueue.cpp

testFills.o: testFills.cpp $(wildcard *.h)
	$(COMPILER) $(COMPILER_OPTS) testFills.cpp

easypng.o: easypng.h easypng.cpp
	$(COMPILER) $(COMPILER_OPTS) easypng.cpp

animation.o: animation.cpp animation.h
	$(COMPILER) $(COMPILER_OPTS) animation.cpp

fills.o: fills.cpp $(wildcard *.h) stack.cpp queue.cpp
	$(COMPILER) $(COMPILER_OPTS) fills.cpp

solidColorPicker.o: colorPicker.h solidColorPicker.cpp solidColorPicker.h
	$(COMPILER) $(COMPILER_OPTS) solidColorPicker.cpp

gridColorPicker.o: colorPicker.h gridColorPicker.cpp gridColorPicker.h
	$(COMPILER) $(COMPILER_OPTS) gridColorPicker.cpp

gradientColorPicker.o: colorPicker.h gradientColorPicker.cpp gradientColorPicker.h
	$(COMPILER) $(COMPILER_OPTS) gradientColorPicker.cpp

rainbowColorPicker.o: colorPicker.h rainbowColorPicker.cpp rainbowColorPicker.h
	$(COMPILER) $(COMPILER_OPTS) rainbowColorPicker.cpp

clean:
	-rm -rf $(EXENAME) testStackQueue *.o images/ frames/ testStackQueue.out testFills.out

