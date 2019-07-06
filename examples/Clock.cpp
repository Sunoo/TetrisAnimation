#include "TetrisMatrixDraw.h"
#include "led-matrix.h"

#include <signal.h>
#include <unistd.h>
#include <iomanip>
#include <thread>

using namespace rgb_matrix;
using std::chrono::system_clock;

RGBMatrix *canvas;

static void InterruptHandler(int signo) {
  canvas->Clear();
  delete canvas;
  
  printf("Received CTRL-C. Exiting.\n");
  exit(0);
}

static int usage(const char *progname, RGBMatrix::Options &matrix_options, rgb_matrix::RuntimeOptions &runtime_opt) {
  fprintf(stderr, "usage: %s [options]\n", progname);
  fprintf(stderr, "Displays the time as a series of falling Tetris blocks.\n");
  fprintf(stderr, "Options:\n");
  rgb_matrix::PrintMatrixFlags(stderr, matrix_options, runtime_opt);
  fprintf(stderr,
          "\t-b <brightness>   : Sets brightness percent. Default: 100.\n"
          "\t-x <x>            : Starting X position of displayed time. Default: 1\n"
          "\t-y <yFinish>      : Ending Y position of displayed time. Default: 16\n"
          "\t-0                : Show leading zeros in the hour.\n"
          "\t-t                : Use 24-hour clock.\n"
          "\t-r                : Force refresh of all digits every minute.\n"
          "\t-d                : Use double size blocks.\n"
          );
  return 1;
}

int main(int argc, char *argv[]) {
  RGBMatrix::Options matrix_options;
  matrix_options.rows = 16;
  rgb_matrix::RuntimeOptions runtime_opt;
  if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv, &matrix_options, &runtime_opt)) {
    return usage(argv[0], matrix_options, runtime_opt);
  }

  int brightness = 100;
  int x = 1;
  int yFinish = 16;
  bool leadingZero = false;
  char *time_format = "%I:%M";
  bool forceRefresh = false;
  int scale = 1;

  int opt;
  while ((opt = getopt(argc, argv, "b:x:y:0trd")) != -1) {
    switch (opt) {
      case 'b':
        brightness = atoi(optarg);
        break;
      case 'x':
        x = atoi(optarg);
        break;
      case 'y':
        yFinish = atoi(optarg);
        break;
      case '0':
        leadingZero = true;
        break;
      case 't':
        time_format = "%H:%M";
        break;
      case 'r':
        forceRefresh = true;
        break;
      case 'd':
        scale = 2;
        break;
      break;
      default:
        return usage(argv[0], matrix_options, runtime_opt);
    }
  }

  if (brightness < 1 || brightness > 100) {
    fprintf(stderr, "Brightness is outside usable range.\n");
    return 1;
  }

  canvas = rgb_matrix::CreateMatrixFromOptions(matrix_options, runtime_opt);
  if (canvas == NULL)
    return 1;

  printf("Size: %dx%d. Hardware gpio mapping: %s\n", canvas->width(), canvas->height(), matrix_options.hardware_mapping);

  canvas->SetBrightness(brightness);
  
  FrameCanvas *offscreen = canvas->CreateFrameCanvas();
  
  TetrisMatrixDraw tetris(*offscreen);
  tetris.scale = scale;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  printf("Press <CTRL-C> to exit and reset LEDs\n");

  while (true) {
      std::time_t tt = system_clock::to_time_t(system_clock::now());
      struct std::tm *ptm = std::localtime(&tt);
      std::stringstream ss;
      ss << std::put_time(ptm, time_format);
      string time = ss.str();
      
      if (!leadingZero && time[0] == '0')
      {
        time[0] = ' ';
      }
      
      tetris.setTime(time, forceRefresh);
      bool finished = false;
      while (!finished)
      {
        offscreen->Clear();
        finished = tetris.drawNumbers(x, yFinish, true);

        usleep(100000);
        canvas->SwapOnVSync(offscreen);
      }

      ++ptm->tm_min;
      ptm->tm_sec=0;
      std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
  }
  return 0;
}
