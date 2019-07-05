#include "TetrisMatrixDraw.h"
#include "led-matrix.h"

#include <unistd.h>
#include <iomanip>
#include <thread>

using namespace rgb_matrix;
using std::chrono::system_clock;

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
  
  TetrisMatrixDraw tetris(*matrix);

  while (true) {
      std::time_t tt = system_clock::to_time_t(system_clock::now());
      struct std::tm *ptm = std::localtime(&tt);
      std::stringstream ss;
      ss << std::put_time(ptm, time_format);
      string time = ss.str();
      
      if (time[0] == '0')
      {
        time[0] = ' ';
      }
      
      tetris.setTime(time);
      bool finished = false;
      while (!finished)
      {
        matrix->Clear();
        finished = tetris.drawNumbers(1, 16, true);

        usleep(100000);
      }

      ++ptm->tm_min;
      ptm->tm_sec=0;
      std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
  }

  // Finished. Shut down the RGB matrix.
  matrix->Clear();
  delete matrix;

  write(STDOUT_FILENO, "\n", 1);  // Create a fresh new line after ^C on screen
  return 0;
}
