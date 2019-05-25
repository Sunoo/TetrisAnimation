# TetrisAnimation

An Arduino library for drawing letters and numbers using a falling block style animation.

[![alt text](https://j.gifs.com/6RvBDl.gif "Tetris clock animation")](https://youtu.be/BGmjvfqf_0U)

Tested using ESP8266 & ESP32 on RGB Led matrixes (using the [PxMatrix library](https://github.com/2dom/PxMatrix/)), but potentially works on any display that uses Adafruit GFX library

## Basic Usage

See examples for more details.

```
//Intialise library by passing in a display
PxMATRIX display(64, 32, P_LAT, P_OE, P_A, P_B, P_C, P_D, P_E);
TetrisMatrixDraw tetris(display);

// Set the value of the library by using setTime, setNumbers or setText

// Usage: setTime(time_string)
// time_string = time in the format "21:23"
tetris.setTime("12:34");

// Usage: setNumbers(num)
// num = Integer value. Max: 999999999 (9 digits long) Min: 0 (negative not currently supported).
tetris.setNumbers(1234);

// Usage: setText(string)
// string = regular text string, Use uppercase letters only.
// For full list of characters supported, check the AlphaTest examples.
tetris.setText("HOWDY!");


// Draw the value

// These will normally be called in a timer or ticker (see any example)
// How often they are called will increase/decrease the speed of which
// the blocks drop.

// Usage: drawNumbers(x, y, showColon) (for use with setTime or setNumber)
// x = most left Pixel of the text 
// y = The bottom of the number when it lands, they will start falling from y + (16 * scale)
// showColon = (optional) show the colon or not, defaults to false (only applicaple when using setTime)
//
// Returns a boolean to indicate if its finished animating
// (will return false if there is still falling blocks)
tetris.drawNumbers(16,8, true);

// Usage: drawText(x, y) (for use with setText)
// x = most left Pixel of the text 
// y = The bottom of the text when it lands, they will start falling from y + (16 * scale)
//
// Returns a boolean to indicate if its finished animating
// (will return false if there is still falling blocks)
tetris.drawText(16,8);


// Scale

// Usage: scale = 2
// Will scale up the size of the characters
// Can be used with either numbers or text 

tetris.scale = 2; // must be called before setText, setTime or setNumbers
tetris.setText("BIG"); // This will be twice the size as normal
delay(5000);
tetris.setText("STILL BIG"); // scale persists
delay(5000);
tetris.scale = 1; // can be reset to normal size if required
tetris.setText("SMALL");
```
