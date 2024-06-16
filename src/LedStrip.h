#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#include "InterpolationCache.h"
#include "LedState.h"
#include "ws2811.h"
#include <vector>

class LedStrip {
private:
  ws2811_t strip;
  InterpolationCache interpolationCache;
  void syncLedState();

public:
  LedStrip(int leds);
  ~LedStrip();

  int numberOfLeds;
  LedState *leds;
  void render();
  void fillAll(Color color);
  void fillAll(uint32_t color);
  void fillAll(Color color, int durationInMilliseconds);
  void fillAll(Color* colors);
  void fillAll(Color* colors, int durationInMilliseconds);
  void fillAll(HSL* hsl, int durationInMilliseconds);
};

#endif
