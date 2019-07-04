/*
Copyright (c) 2018 Tobias Blum . All right reserved.

Tetris Matrix Clock

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#ifndef TetrisMatrixDraw_h
#define TetrisMatrixDraw_h

#include "led-matrix.h"
#include "graphics.h"
#include <iostream>

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

using namespace std;
using namespace rgb_matrix;

#define TETRIS_MAX_NUMBERS 9

#define TETRIS_DISTANCE_BETWEEN_DIGITS 7
#define TETRIS_Y_DROP_DEFAULT 16

// Type that describes the current state of a drawn number
typedef struct
{
  int num_to_draw; // Number to draw (0-9)
  int blockindex;  // The index of the brick (as defined in the falling instructions) that is currently falling
  int fallindex;   // y-position of the brick it already has (incrementing with each step)
  int x_shift;     // x-position of the number relative to the matrix where the number should be placed.
} numstate;

class TetrisMatrixDraw
{
    public:
        TetrisMatrixDraw (Canvas  &display);
        Canvas  *display;
        bool drawNumbers(int x = 0, int y = 0, bool displayColon = false);
        bool drawText(int x = 0, int y = 0);
        void drawChar(string letter, uint8_t x, uint8_t y, Color color);
        void drawShape(int blocktype, Color color, int x_pos, int y_pos, int num_rot);
        void drawLargerShape(int scale, int blocktype, Color color, int x_pos, int y_pos, int num_rot);
        void setTime(string time, bool forceRefresh = false);
        void setNumbers(int value, bool forceRefresh = false);
        void setText(string txt, bool forceRefresh = false);
        void setNumState(int index, int value, int x_shift);
        void drawColon(int x, int y, Color colonColour);
        int calculateWidth();
        bool _debug = false;
        int scale = 1;
        bool drawOutline = false;
        Color outLineColour = Color(0, 0, 0);

        Color tetrisColors[9];
        Color tetrisRED;
        Color tetrisGREEN;
        Color tetrisBLUE;
        Color tetrisWHITE;
        Color tetrisYELLOW;
        Color tetrisCYAN;
        Color tetrisMAGENTA;
        Color tetrisORANGE;
        Color tetrisBLACK;

    private:
        void intialiseColors();
        void resetNumStates();
        void drawLargerBlock(int x_pos, int y_pos, int scale, Color color);
        void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color color);
        numstate numstates[TETRIS_MAX_NUMBERS];
        int sizeOfValue;
};

#endif
