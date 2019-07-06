# TetrisAnimation

A library for drawing letters and numbers using a falling block style animation on the Raspberry Pi.

[![alt text](https://j.gifs.com/6RvBDl.gif "Tetris clock animation")](https://youtu.be/BGmjvfqf_0U)

### Displays/Libraries tested ( Examples included)
- RGB LED Matrix using the [rpi-rgb-led-matrix library](https://github.com/hzeller/rpi-rgb-led-matrix/) - Raspberry Pi

## Basic Usage

See examples for more details.

### Intialise library by passing in a display:

```
Canvas *display = rgb_matrix::CreateMatrixFromFlags(&argc, &argv); //Intialise any display that makes use of rpi-rgb-led-matrix
TetrisMatrixDraw tetris(display); //Pass it into the library

```

### Set the value:

Set the value of the library by using one of: setTime, setNumbers or setText commands

```
// Usage: setTime(time_string, forceRefresh = false)
// time_string = time in the format "21:23"
// forceRefresh: by default, a digit will only redraw if it's value has changed
//               (so for a clock the hour digit would only draw once an hour)
//               but setting this value to true tells the library to redraw
//               all the digits.  
tetris.setTime("12:34");

// Usage: setNumbers(num, forceRefresh = false)
// num = Integer value. Max: 999999999 (9 digits long) Min: 0 (negative not currently supported).
// forceRefresh: by default, a digit will only redraw if it's value has changed
//               (so for a clock the hour digit would only draw once an hour)
//               but setting this value to true tells the library to redraw
//               all the digits.  
tetris.setNumbers(1234);

// Usage: setText(string, forceRefresh = false)
// string = regular text string, Use uppercase letters only.
// forceRefresh: by default, a digit will only redraw if it's value has changed
//               (so for a clock the hour digit would only draw once an hour)
//               but setting this value to true tells the library to redraw
//               all the digits.
//
// For full list of characters supported, check the AlphaTest examples.
tetris.setText("HOWDY!");

```

### Draw the value:

These will normally be called in a timer or ticker (see any example). How often they are called will increase/decrease the speed of which the blocks drop.

```

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

```

### Scale the font:

```
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
