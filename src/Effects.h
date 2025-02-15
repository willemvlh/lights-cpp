#pragma once

#include "Color.h"
#include "Strip.h"
class Effects {
private:
  Strip *_strip;

public:
  Effects(Strip *strip);
  void gradient(std::vector<Color>, int durationsInMilliseconds);
  void wheel(int iterations, bool reverse);
  void shift();
  void shiftGradient(int);
  void pulse(int durationInMilliseconds, int iterations);
  void palettes();
  void palettes_static();
};
