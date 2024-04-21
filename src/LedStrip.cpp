#include "LedStrip.h"
#include "util.h"
#include "ws2811.h"
#include <iostream>




LedStrip::LedStrip(int leds) {
  this->numberOfLeds = leds;

  ws2811_t ledStrip = {.freq = WS2811_TARGET_FREQ, .dmanum = 10};

  ledStrip.channel[0].gpionum = 18;
  ledStrip.channel[0].count = leds;
  ledStrip.channel[0].strip_type = WS2811_STRIP_RGB;
  ledStrip.channel[0].invert = 0;
  ledStrip.channel[0].brightness = 255;
  LedState *ledStates = new LedState[leds];
  this->strip = ledStrip;
  this->leds = ledStates;
  if (ws2811_init(&this->strip) != WS2811_SUCCESS) {
    std::cerr << "Error" << std::endl;
  }
  for (int i = 0; i < leds; i++) {
    ledStates[i] = {0, 0, 0};
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

void LedStrip::fillAll(Color color, int durationInMilliseconds) {
  int steps = 10;
  for (int index = 0; index < steps; index++) {
    for (int i = 0; i < numberOfLeds; i++) {
      leds[i].color = color;
    }
    render();
    Utility::waitFor(durationInMilliseconds / steps);
  }
}

void LedStrip::fillAll(Color color) { fillAll(color, 0); }

void LedStrip::fillAll(uint32_t color) {
  Color color2 = {};
  color2.red = color >> 16 & 0xff;
  color2.green = color >> 8 & 0xff;
  color2.blue = color & 0xff;
  fillAll(color2);
}

