# Specify the target file and the install directory
OUTPUTFILE = libTetrisAnimation.a

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libjohnpaul.a from john.o, paul.o, and johnpaul.o
$(OUTPUTFILE): TetrisMatrixDraw.o
	ar rcs $@ $^

# No rule to build john.o, paul.o, and johnpaul.o from .cpp 
# files is required; this is handled by make's database of
# implicit rules

.PHONY: clean
clean:
	rm -f TetrisMatrixDraw.o libTetrisAnimation.a

# Indicate dependencies of .ccp files on .hpp files
TetrisMatrixDraw.o:
	g++ -I. -I/home/pi/rpi-rgb-led-matrix/include -c TetrisMatrixDraw.cpp -o $@
