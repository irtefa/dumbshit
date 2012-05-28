
###############################################################################
#                                                                             #
#  CS225 Maze Makefile                                                        #
#                                                                             #
#  Author: Daniel Hoodin                                                      #
#  Date: Spring 2009                                                          #
#                                                                             #
###############################################################################

TEST_SQUARE_MAZE_EXE = testsquaremaze
TEST_DSETS_EXE = testdsets
TEST_DSETS_OBJS = testdsets.o dsets.o
TEST_SQUARE_MAZE_OBJS = testsquaremaze.o maze.o dsets.o easypng.o

CXX = g++
WARNINGS = -Wchar-subscripts -Wparentheses -Wreturn-type -Wmissing-braces -Wundef -Wshadow
CXX_OPTS = -c -g -O0 -Wfatal-errors -Werror $(WARNINGS)

.PHONY: all clean

all: $(TEST_DSETS_EXE) $(TEST_SQUARE_MAZE_EXE)

clean:
	-rm *.o $(TEST_DSETS_EXE) $(TEST_SQUARE_MAZE_EXE) 2>/dev/null

$(TEST_DSETS_EXE): $(TEST_DSETS_OBJS)
	$(CXX) -o $@ $^

$(TEST_SQUARE_MAZE_EXE): $(TEST_SQUARE_MAZE_OBJS)
	$(CXX) $^ -lpng -o $@

testdsets.o: testdsets.cpp dsets.o
	$(CXX) $(CXX_OPTS) $<

testsquaremaze.o: testsquaremaze.cpp dsets.o maze.o easypng.o
	$(CXX) $(CXX_OPTS) $<

dsets.o: dsets.cpp dsets.h
	$(CXX) $(CXX_OPTS) $<

maze.o: maze.cpp maze.h dsets.o
	$(CXX) $(CXX_OPTS) $<

easypng.o: easypng.cpp easypng.h
	$(CXX) $(CXX_OPTS) $<

