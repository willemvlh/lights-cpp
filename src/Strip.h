#pragma once
#include "InterpolationCache.h"
#include "LedState.h"
#include "ws2811.h"
#include <vector>

class Strip {

public:
  Strip(int leds);
  virtual ~Strip();

  int numberOfLeds;
  LedState *leds;
  virtual void render() = 0;
  void fillAll(Color color);
  void fillAll(uint32_t color);
  void fillAll(Color color, int durationInMilliseconds);
  void fillAll(Color* colors);
  void fillAll(Color* colors, int durationInMilliseconds);
  void fillAll(HSL* hsl, int durationInMilliseconds);
private:
  InterpolationCache interpolationCache;
};
