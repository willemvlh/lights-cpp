#if CAN_USE_STRIP
#include "LedStrip.h"
#include "LedState.h"
#include "util.h"
#include "ws2811/ws2811.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>

LedStrip::LedStrip(int leds) : Strip(leds) {
  ws2811_t ledStrip = {.freq = WS2811_TARGET_FREQ, .dmanum = 10};
  ledStrip.channel[0].gpionum = 18;
  ledStrip.channel[0].count = leds;
  ledStrip.channel[0].strip_type = WS2811_STRIP_GRB;
  ledStrip.channel[0].invert = 0;
  ledStrip.channel[0].brightness = 255;
  this->strip = ledStrip;
  if (ws2811_init(&this->strip) != WS2811_SUCCESS) {
    std::cerr << "Error" << std::endl;
  }
  syncLedState();
}

LedStrip::~LedStrip() {
  std::cout << "Cleaning-up..." << std::endl;
  ws2811_fini(&strip);
}

void LedStrip::syncLedState() {
  for (int i = 0; i < numberOfLeds; i++) {
    strip.channel[0].leds[i] = leds[i].toInteger();
  }
}

void LedStrip::render() {
  syncLedState();
  ws2811_render(&strip);
}
#endif
