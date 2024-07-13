#include "Strip.h"
#include "LedState.h"
#include "TimingFunction.h"
#include "util.h"
#include "ws2811/ws2811.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>

Strip::Strip(int leds) : numberOfLeds(leds) {
  this->leds = new LedState[leds];
  for (int i = 0; i < leds; i++) {
    this->leds[i] = {0, 0, 0};
  }
}
Strip::~Strip(){};

void Strip::fillAll(Color *colors, int durationInMilliseconds,
                    TimingFunction &fn) {
  int denominator = std::stoi(Utility::readEnv("LIGHTS_STEPS_DENOMINATOR", "10"));  
  int steps = std::max(1, durationInMilliseconds / denominator);
  auto interpolations = std::vector<std::vector<Color>>(numberOfLeds);
  for (int i = 0; i < numberOfLeds; i++) {
    interpolations[i] = leds[i].color.interpolate(colors[i], steps);
  }
  for (int step = 0; step < steps; step++) {
    for (int i = 0; i < numberOfLeds; i++) {
      int timingAdaptedStep = fn(step, steps);  
      leds[i].color =
          interpolations[i][timingAdaptedStep + 1]; // interpolation includes starting color,
                                       // which we skip by doing step+1
    }
    auto start = std::chrono::high_resolution_clock::now();
    render();
    auto duration = std::chrono::high_resolution_clock::now() - start;
    auto duration_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    if (durationInMilliseconds > 0) {
      Utility::waitFor(durationInMilliseconds / steps - duration_ms);

    }
  }
}

void Strip::fillAll(Color *colors, int durationInMilliseconds) {
  Linear t;
  fillAll(colors, durationInMilliseconds, t);
}
void Strip::fillAll(Color color, int durationInMilliseconds, TimingFunction &fn) {
  Color colors[numberOfLeds];
  std::fill(colors, colors + numberOfLeds, color);
  fillAll(colors, durationInMilliseconds, fn);
}
void Strip::fillAll(Color color, int durationInMilliseconds){
    Linear t;
    fillAll(color, durationInMilliseconds, t);
}

void Strip::fillAll(Color color) { fillAll(color, 0); }
void Strip::fillAll(Color *colors) { fillAll(colors, 0); }

void Strip::fillAll(uint32_t color) {
  Color color2 = {};
  color2.red = color >> 16 & 0xff;
  color2.green = color >> 8 & 0xff;
  color2.blue = color & 0xff;
  fillAll(color2);
}

void Strip::fillAll(std::vector<Color> colors, int durationInMilliseconds) {
  fillAll(&colors[0], durationInMilliseconds);
}

void Strip::fillAll(std::vector<Color> colors) { fillAll(colors, 0); }

void Strip::fillAll(HSL *hsl, int durationInMilliseconds) {
  Color color[numberOfLeds];
  for (int i = 0; i < numberOfLeds; i++) {
    color[i] = Color::fromHSL(hsl[i]);
  }
  fillAll(color, durationInMilliseconds);
}
