RGB_LIB_DISTRIBUTION=/home/pi/rpi-rgb-led-matrix
TETRIS_LIB_DISTRIBUTION=..

CXXFLAGS=-Wall -O3 -g -Wextra -Wno-unused-parameter

all : Clock

Clock: Clock.o
	$(CXX) $(CXXFLAGS) Clock.o -o $@ -L$(RGB_LIB_DISTRIBUTION)/lib -lrgbmatrix -L$(TETRIS_LIB_DISTRIBUTION)/src -lTetrisAnimation -lrt -lm -lpthread

%.o : %.cpp
	$(CXX) -I$(RGB_LIB_DISTRIBUTION)/include -I$(TETRIS_LIB_DISTRIBUTION)/src $(CXXFLAGS) -c -o $@ $<

Clock.o : Clock.cpp
	$(CXX) -I$(RGB_LIB_DISTRIBUTION)/include -I$(TETRIS_LIB_DISTRIBUTION)/src $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f Clock.o Clock
