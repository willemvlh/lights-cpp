#pragma once
#include "InterpolationCache.h"
#include "LedState.h"
#include "TimingFunction.h"
#include "ws2811/ws2811.h"
#include <vector>

class Strip {

public:
  Strip(int leds);
  virtual ~Strip();

  int numberOfLeds;
  LedState *leds;
  void fillAll(Color color);
  void fillAll(uint32_t color);
  void fillAll(Color color, int durationInMilliseconds);
  void fillAll(Color color, int durationInMilliseconds, TimingFunction &);
  void fillAll(Color *colors);
  void fillAll(Color *colors, int durationInMilliseconds);
  void fillAll(Color *colors, int durationInMilliseconds, TimingFunction&);
  void fillAll(std::vector<Color> colors, int durationInMilliseconds);
  void fillAll(std::vector<Color> colors);
  void fillAll(HSL *hsl, int durationInMilliseconds);

private:
  virtual void render() = 0;
  InterpolationCache interpolationCache;
};
