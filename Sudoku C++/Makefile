CXXFLAGS=-std=c++11 -stdlib=libc++ -Wall -O3
LDFLAGS=-lm -larmadillo
OBJ=solver.o altproj.o game.o tests.o

all: $(OBJ)
	$(CXX) main.cpp -o sudoku $(OBJ) $(CXXFLAGS) $(LDFLAGS)
