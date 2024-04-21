#ifndef LEDSTRIP_H
#define LEDSTRIP_H
#include "ws2811.h"
#include "LedState.h"

class LedStrip {
private:
  ws2811_t strip;
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
};

#endif
