#include "TetrisMatrixDraw.h"
#include "led-matrix.h"
#include "graphics.h"

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

using namespace rgb_matrix;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

int main(int argc, char *argv[]) {
  RGBMatrix::Options matrix_options;
  matrix_options.rows = 16;
  rgb_matrix::RuntimeOptions runtime_opt;
  rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt);

  //const char *time_format = "%H:%M";
  const char *time_format = "%I:%M";
  
  int brightness = 100;

  if (brightness < 1 || brightness > 100) {
    fprintf(stderr, "Brightness is outside usable range.\n");
    return 1;
  }

  RGBMatrix *matrix = rgb_matrix::CreateMatrixFromOptions(matrix_options, runtime_opt);
  if (matrix == NULL)
    return 1;

  matrix->SetBrightness(brightness);

  char text_buffer[6];
  time_t rawtime;
  struct tm *timeinfo;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  TetrisMatrixDraw tetris(*matrix);

  while (!interrupt_received) {
      time(&rawtime);
      timeinfo = localtime(&rawtime);
      strftime(text_buffer, 6, time_format, timeinfo);

      tetris.setTime(text_buffer);
      bool finished = false;
      while (!finished && !interrupt_received)
      {
        matrix->Clear();
        finished = tetris.drawNumbers(1, 16, true);

        usleep(100000);
      }

      sleep(1);
  }

  // Finished. Shut down the RGB matrix.
  matrix->Clear();
  delete matrix;

  write(STDOUT_FILENO, "\n", 1);  // Create a fresh new line after ^C on screen
  return 0;
}
