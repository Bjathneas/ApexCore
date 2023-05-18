#pragma once

#include "ApexCore/Graphics/Color.h"
#include "ApexCore/LogCore.h"

namespace ApexCore {
  
constexpr static float PI = 3.14159265359;

struct WINDOW {
  int WIDTH;
  int HEIGHT;
  int FPS;
  const char *TITLE;
  double DELTA_TIME;
  Color COLOR;
};

extern WINDOW WINDOW;

struct MOUSE {
  double X, Y;
};

extern MOUSE MOUSE;

extern Logger LOG;
} // namespace ApexCore
