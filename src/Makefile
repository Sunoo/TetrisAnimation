RGB_LIB_DISTRIBUTION=/home/pi/rpi-rgb-led-matrix

all: libTetrisAnimation.a

libTetrisAnimation.a: TetrisMatrixDraw.o
	ar rcs $@ $^

clean:
	rm -f TetrisMatrixDraw.o libTetrisAnimation.a

TetrisMatrixDraw.o:
	g++ -I. -I$(RGB_LIB_DISTRIBUTION)/include -c TetrisMatrixDraw.cpp -o $@
