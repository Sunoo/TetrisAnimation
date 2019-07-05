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


#include "TetrisMatrixDraw.h"
#include "TetrisNumbers.h"
#include "TetrisLetters.h"
#include <algorithm>

TetrisMatrixDraw::TetrisMatrixDraw(Canvas &display)	{
    this->display = &display;
    intialiseColors();
    resetNumStates();
}

// *********************************************************************
// Draws a brick shape at a given position
// *********************************************************************
void TetrisMatrixDraw::drawShape(int blocktype, Color color, int x_pos, int y_pos, int num_rot)
{
  // Square
  if (blocktype == 0)
  {
    this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
    this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
    this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
    this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
  }

  // L-Shape
  if (blocktype == 1)
  {
    if (num_rot == 0)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 2, color.r, color.g, color.b);
    }
    if (num_rot == 1)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos - 1, color.r, color.g, color.b);
    }
    if (num_rot == 2)
    {
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 2, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 2, color.r, color.g, color.b);
    }
    if (num_rot == 3)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos - 1, color.r, color.g, color.b);
    }
  }

  // L-Shape (reverse)
  if (blocktype == 2)
  {
    if (num_rot == 0)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 2, color.r, color.g, color.b);
    }
    if (num_rot == 1)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
    }
    if (num_rot == 2)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 2, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 2, color.r, color.g, color.b);
    }
    if (num_rot == 3)
    {
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos, color.r, color.g, color.b);
    }
  }

  // I-Shape
  if (blocktype == 3)
  {
    if (num_rot == 0 || num_rot == 2)
    { // Horizontal
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 3, y_pos, color.r, color.g, color.b);
    }
    if (num_rot == 1 || num_rot == 3)
    { // Vertical
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 2, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 3, color.r, color.g, color.b);
    }
  }

  // S-Shape
  if (blocktype == 4)
  {
    if (num_rot == 0 || num_rot == 2)
    {
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 2, color.r, color.g, color.b);
    }
    if (num_rot == 1 || num_rot == 3)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos - 1, color.r, color.g, color.b);
    }
  }

  // S-Shape (reversed)
  if (blocktype == 5)
  {
    if (num_rot == 0 || num_rot == 2)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 2, color.r, color.g, color.b);
    }
    if (num_rot == 1 || num_rot == 3)
    {
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
    }
  }

  // Half cross
  if (blocktype == 6)
  {
    if (num_rot == 0)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
    }
    if (num_rot == 1)
    {
      this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 2, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
    }
    if (num_rot == 2)
    {
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 2, y_pos - 1, color.r, color.g, color.b);
    }
    if (num_rot == 3)
    {
      this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
      this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
      this->display->SetPixel(x_pos + 1, y_pos - 2, color.r, color.g, color.b);
    }
  }

   // Corner-Shape 
   if (blocktype == 7)
   {
     if (num_rot == 0)
     {
       this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
       this->display->SetPixel(x_pos + 1, y_pos, color.r, color.g, color.b);
       this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
     }
     if (num_rot == 1)
     {
       this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
       this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
       this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
     }
     if (num_rot == 2)
     {
       this->display->SetPixel(x_pos + 1 , y_pos, color.r, color.g, color.b);
       this->display->SetPixel(x_pos + 1 , y_pos - 1, color.r, color.g, color.b);
       this->display->SetPixel(x_pos, y_pos - 1, color.r, color.g, color.b);
     }
     if (num_rot == 3)
     {
       this->display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
       this->display->SetPixel(x_pos + 1, y_pos , color.r, color.g, color.b);
       this->display->SetPixel(x_pos + 1, y_pos - 1, color.r, color.g, color.b);
     }
   }
}

void TetrisMatrixDraw::drawLargerBlock(int x_pos, int y_pos, int scale, Color color){
  fillRect(x_pos, y_pos, scale, scale, color);
  if(drawOutline){
    drawRect(x_pos, y_pos, scale, scale, this->outLineColour);
  }
}

void TetrisMatrixDraw::drawLargerShape(int scale, int blocktype, Color color, int x_pos, int y_pos, int num_rot)
{
  int offset1 = 1 * scale;
  int offset2 = 2 * scale;
  int offset3 = 3 * scale;

  // Square
  if (blocktype == 0)
  {
    this->drawLargerBlock(x_pos, y_pos, scale, color);
    this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
    this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
    this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
  }

  // L-Shape
  if (blocktype == 1)
  {
    if (num_rot == 0)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);

    }
    if (num_rot == 1)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);

    }
    if (num_rot == 2)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);

    }
    if (num_rot == 3)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);
    }
  }

  // L-Shape (reverse)
  if (blocktype == 2)
  {
    if (num_rot == 0)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
    }
    if (num_rot == 1)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
    }
    if (num_rot == 2)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
    }
    if (num_rot == 3)
    {
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
    }
  }

  // I-Shape
  if (blocktype == 3)
  {
    if (num_rot == 0 || num_rot == 2)
    { // Horizontal
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset3, y_pos, scale, color);
    }
    if (num_rot == 1 || num_rot == 3)
    { // Vertical
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset3, scale, color);
    }
  }

  // S-Shape
  if (blocktype == 4)
  {
    if (num_rot == 0 || num_rot == 2)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);
    }
    if (num_rot == 1 || num_rot == 3)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);
    }
  }

  // S-Shape (reversed)
  if (blocktype == 5)
  {
    if (num_rot == 0 || num_rot == 2)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
    }
    if (num_rot == 1 || num_rot == 3)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
    }
  }

  // Half cross
  if (blocktype == 6)
  {
    if (num_rot == 0)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
    }
    if (num_rot == 1)
    {
      this->drawLargerBlock(x_pos, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset2, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
    }
    if (num_rot == 2)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset2, y_pos - offset1, scale, color);
    }
    if (num_rot == 3)
    {
      this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
      this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
      this->drawLargerBlock(x_pos + offset1, y_pos - offset2, scale, color);
    }
  }

   // Corner-Shape 
   if (blocktype == 7)
   {
     if (num_rot == 0)
     {
       this->drawLargerBlock(x_pos, y_pos, scale, color);
       this->drawLargerBlock(x_pos + offset1, y_pos, scale, color);
       this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
     }
     if (num_rot == 1)
     {
       this->drawLargerBlock(x_pos, y_pos, scale, color);
       this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
       this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
     }
     if (num_rot == 2)
     {
       this->drawLargerBlock(x_pos + offset1 , y_pos, scale, color);
       this->drawLargerBlock(x_pos + offset1 , y_pos - offset1, scale, color);
       this->drawLargerBlock(x_pos, y_pos - offset1, scale, color);
     }
     if (num_rot == 3)
     {
       this->drawLargerBlock(x_pos, y_pos, scale, color);
       this->drawLargerBlock(x_pos + offset1, y_pos , scale, color);
       this->drawLargerBlock(x_pos + offset1, y_pos - offset1, scale, color);
     }
   }
}

void TetrisMatrixDraw::setNumState(int index, int value, int x_shift)
{
    if(index < TETRIS_MAX_NUMBERS) {
      //cout << value << endl;
        this->numstates[index].num_to_draw = value;
        this->numstates[index].x_shift = x_shift;
        this->numstates[index].fallindex = 0;
        this->numstates[index].blockindex = 0;
    }
}

void TetrisMatrixDraw::setTime(string time, bool forceRefresh)
{
    this->sizeOfValue = 4;
    time.erase(std::remove(time.begin(), time.end(), ':'), time.end());
    for (uint8_t pos = 0; pos < 4; pos++)
    {
      int xOffset = pos * TETRIS_DISTANCE_BETWEEN_DIGITS * this->scale;
      if(pos >= 2){
        xOffset += (3 * this->scale);
      }
      string individualNumber = time.substr(pos, 1);
      int number = (individualNumber != " ") ? stoi(individualNumber) : -1;
      // Only change the number if its different or being forced
      if (forceRefresh || number != this->numstates[pos].num_to_draw)
      {
        setNumState(pos, number, xOffset);
      }
    }
}

void TetrisMatrixDraw::setNumbers(int value, bool forceRefresh)
{
  string strValue = to_string(value);
  if(strValue.length() <= TETRIS_MAX_NUMBERS){
    this->sizeOfValue = strValue.length();
    int currentXShift = 0;
    for (uint8_t pos = 0; pos < this->sizeOfValue; pos++)
    {
      currentXShift = TETRIS_DISTANCE_BETWEEN_DIGITS * this->scale * pos;
      int number = stoi(strValue.substr(pos, 1));
      // Only change the number if its different or being forced
      if (forceRefresh || number != this->numstates[pos].num_to_draw)
      {
        setNumState(pos, number, currentXShift);
      } else {
        this->numstates[pos].x_shift = currentXShift;
      }
    }
  } else {
    //cout << "Number too long" << endl;
  }
}

void TetrisMatrixDraw::setText(string txt, bool forceRefresh)
{
    this->sizeOfValue = txt.length();
    int currentXShift = 0;
    for (uint8_t pos = 0; pos < this->sizeOfValue; pos++)
    {
      currentXShift = TETRIS_DISTANCE_BETWEEN_DIGITS * this->scale * pos;
      char letter = txt[pos];
      if (forceRefresh || (int)letter != this->numstates[pos].num_to_draw)
      {
        setNumState(pos, (int)letter, currentXShift);
      } else {
        this->numstates[pos].x_shift = currentXShift;
      }
    }
}

bool TetrisMatrixDraw::drawText(int x, int yFinish)
{
  // For each number position
  bool finishedAnimating = true;

  int scaledYOffset = (this->scale > 1) ? this->scale : 1;
  int y = yFinish - (TETRIS_Y_DROP_DEFAULT * this->scale);

  // For each number position
  for (int numpos = 0; numpos < this->sizeOfValue; numpos++)
  {

    if(numstates[numpos].num_to_draw >= 33)
    {
      // Draw falling shape
      if (numstates[numpos].blockindex < blocksPerChar[numstates[numpos].num_to_draw-33])
      {
        finishedAnimating = false;
        fall_instr_let current_fall = getFallinstrByAscii(numstates[numpos].num_to_draw, numstates[numpos].blockindex);

        // Handle variations of rotations
        uint8_t rotations = current_fall.num_rot;
        if (rotations == 1)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 2))
          {
            rotations = 0;
          }
        }
        if (rotations == 2)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 3))
          {
            rotations = 0;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 3 * 2))
          {
            rotations = 1;
          }
        }
        if (rotations == 3)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4))
          {
            rotations = 0;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4 * 2))
          {
            rotations = 1;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4 * 3))
          {
            rotations = 2;
          }
        }
        if(this->scale <= 1){
          drawShape(current_fall.blocktype, 
                    this->tetrisColors[current_fall.color],
                    x + current_fall.x_pos + numstates[numpos].x_shift, 
                    y + numstates[numpos].fallindex - scaledYOffset, 
                    rotations);
        } else {
          drawLargerShape(this->scale, 
                          current_fall.blocktype, 
                          this->tetrisColors[current_fall.color], 
                          x + (current_fall.x_pos * this->scale) + numstates[numpos].x_shift, 
                          y + (numstates[numpos].fallindex * scaledYOffset) - scaledYOffset, 
                          rotations);
        }
        numstates[numpos].fallindex++;

        if (numstates[numpos].fallindex > current_fall.y_stop)
        {
          numstates[numpos].fallindex = 0;
          numstates[numpos].blockindex++;
        }
      }

      // Draw already dropped shapes
      if (numstates[numpos].blockindex > 0)
      {
        for (int i = 0; i < numstates[numpos].blockindex; i++)
        {
          fall_instr_let fallen_block = getFallinstrByAscii(numstates[numpos].num_to_draw, i);
          if(this->scale <= 1){
            drawShape(fallen_block.blocktype, 
                      this->tetrisColors[fallen_block.color], 
                      x + fallen_block.x_pos + numstates[numpos].x_shift, 
                      y + fallen_block.y_stop - 1, 
                      fallen_block.num_rot);
          } else {
            drawLargerShape(this->scale, 
                            fallen_block.blocktype, 
                            this->tetrisColors[fallen_block.color], 
                            x + (fallen_block.x_pos * this->scale) + numstates[numpos].x_shift, 
                            y + (fallen_block.y_stop * scaledYOffset) - scaledYOffset, 
                            fallen_block.num_rot);
          }
        }
      }
    }
    
  }

  return finishedAnimating;
}

bool TetrisMatrixDraw::drawNumbers(int x, int yFinish, bool displayColon)
{
  // For each number position
  bool finishedAnimating = true;

  int scaledYOffset = (this->scale > 1) ? this->scale : 1;
  int y = yFinish - (TETRIS_Y_DROP_DEFAULT * this->scale);

  for (int numpos = 0; numpos < this->sizeOfValue; numpos++)
  {
    if(numstates[numpos].num_to_draw >= 0) 
    {
      // Draw falling shape
      if (numstates[numpos].blockindex < blocksPerNumber[numstates[numpos].num_to_draw])
      {
        finishedAnimating = false;
        fall_instr current_fall = getFallinstrByNum(numstates[numpos].num_to_draw, numstates[numpos].blockindex);

        // Handle variations of rotations
        uint8_t rotations = current_fall.num_rot;
        if (rotations == 1)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 2))
          {
            rotations = 0;
          }
        }
        if (rotations == 2)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 3))
          {
            rotations = 0;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 3 * 2))
          {
            rotations = 1;
          }
        }
        if (rotations == 3)
        {
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4))
          {
            rotations = 0;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4 * 2))
          {
            rotations = 1;
          }
          if (numstates[numpos].fallindex < (int)(current_fall.y_stop / 4 * 3))
          {
            rotations = 2;
          }
        }

        if(this->scale <= 1){
          drawShape(current_fall.blocktype, 
                    this->tetrisColors[current_fall.color],
                    x + current_fall.x_pos + numstates[numpos].x_shift, 
                    y + numstates[numpos].fallindex - scaledYOffset, 
                    rotations);
        } else {
          drawLargerShape(this->scale, 
                          current_fall.blocktype, 
                          this->tetrisColors[current_fall.color], 
                          x + (current_fall.x_pos * this->scale) + numstates[numpos].x_shift, 
                          y + (numstates[numpos].fallindex * scaledYOffset) - scaledYOffset, 
                          rotations);
        }
        numstates[numpos].fallindex++;

        if (numstates[numpos].fallindex > current_fall.y_stop)
        {
          numstates[numpos].fallindex = 0;
          numstates[numpos].blockindex++;
        }
      }

      // Draw already dropped shapes
      if (numstates[numpos].blockindex > 0)
      {
        for (int i = 0; i < numstates[numpos].blockindex; i++)
        {
          fall_instr fallen_block = getFallinstrByNum(numstates[numpos].num_to_draw, i);
          if(this->scale <= 1){
            drawShape(fallen_block.blocktype, 
                      this->tetrisColors[fallen_block.color], 
                      x + fallen_block.x_pos + numstates[numpos].x_shift, 
                      y + fallen_block.y_stop - 1, 
                      fallen_block.num_rot);
          } else {
            drawLargerShape(this->scale, 
                            fallen_block.blocktype, 
                            this->tetrisColors[fallen_block.color], 
                            x + (fallen_block.x_pos * this->scale) + numstates[numpos].x_shift, 
                            y + (fallen_block.y_stop * scaledYOffset) - scaledYOffset, 
                            fallen_block.num_rot);
          }
        }
      }
    }
  }

  if (displayColon)
  {
    this->drawColon(x, y, this->tetrisWHITE);
  }

  return finishedAnimating;
}

void TetrisMatrixDraw::drawColon(int x, int y, Color colonColour){
  int colonSize = 2 * this->scale;
  int xColonPos = x + (TETRIS_DISTANCE_BETWEEN_DIGITS * 2 * this->scale);  
  fillRect(xColonPos, y + (12 * this->scale), colonSize, colonSize, colonColour);
  fillRect(xColonPos, y + (8 * this->scale), colonSize, colonSize, colonColour);
}

void TetrisMatrixDraw::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color color){
  for (int16_t x_pos = x; x_pos < x + w; x_pos++){
    for (int16_t y_pos = y; y_pos < y + h; y_pos++){
      display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
    }
  }
}

void TetrisMatrixDraw::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, Color color){
  for (int16_t x_pos = x; x_pos < x + w; x_pos++){
    for (int16_t y_pos = y; y_pos < y + h; y_pos++){
      if ((x_pos == x || x_pos == x + w - 1) || (y_pos == y || y_pos == y + h - 1)){
        display->SetPixel(x_pos, y_pos, color.r, color.g, color.b);
      }
    }
  }
}

void TetrisMatrixDraw::intialiseColors(){
    this->tetrisRED = Color(255, 0, 0);
    this->tetrisGREEN = Color(0, 255, 0);
    this->tetrisBLUE = Color(49, 73, 255);
    this->tetrisWHITE = Color(255, 255, 255);
    this->tetrisYELLOW = Color(255, 255, 0);
    this->tetrisCYAN = Color(0, 255, 255);
    this->tetrisMAGENTA = Color(255, 0, 255);
    this->tetrisORANGE = Color(255, 97, 0);
    this->tetrisBLACK = Color(0, 0, 0);
    
    this->tetrisColors[0] = this->tetrisRED; 
    this->tetrisColors[1] = this->tetrisGREEN; 
    this->tetrisColors[2] = this->tetrisBLUE; 
    this->tetrisColors[3] = this->tetrisWHITE; 
    this->tetrisColors[4] = this->tetrisYELLOW; 
    this->tetrisColors[5] = this->tetrisCYAN; 
    this->tetrisColors[6] = this->tetrisMAGENTA;
    this->tetrisColors[7] = this->tetrisORANGE; 
    this->tetrisColors[8] = this->tetrisBLACK;
}

int TetrisMatrixDraw::calculateWidth(){
  return (this->sizeOfValue * TETRIS_DISTANCE_BETWEEN_DIGITS) - 1;
}

void TetrisMatrixDraw::resetNumStates(){
    for(int i = 0; i < TETRIS_MAX_NUMBERS; i++){
        this->numstates[i].num_to_draw = -1;
        this->numstates[i].fallindex = 0;
        this->numstates[i].blockindex = 0;
        this->numstates[i].x_shift = 0;
    }
}
