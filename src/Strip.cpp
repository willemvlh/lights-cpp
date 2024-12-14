#include "Strip.h"
#include "LedState.h"
#include "TimingFunction.h"
#include "util.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>

Strip::Strip(int leds) : numberOfLeds(leds) {
  this->leds = new LedState[leds];
  for (int i = 0; i < leds; i++) {
    this->leds[i] = {0, 0, 0};
  }
}
Strip::~Strip() { delete[] this->leds; };

void Strip::fillAll(Color *colors, int durationInMilliseconds,
                    TimingFunction &fn) {
  int steps =
      std::max(1, durationInMilliseconds); // optimize later if necessary
  auto interpolations = std::vector<std::vector<Color>>(numberOfLeds);
  for (int i = 0; i < numberOfLeds; i++) {
    interpolations[i] = leds[i].color.interpolate(colors[i], steps);
  }
  for (int step = 0; step < steps; step++) {
    for (int i = 0; i < numberOfLeds; i++) {
      int timingAdaptedStep = fn(step, steps);
      leds[i].color =
          interpolations[i][timingAdaptedStep +
                            1]; // interpolation includes starting color,
                                // which we skip by doing step+1
    }
#ifndef NORENDER
    auto start = std::chrono::high_resolution_clock::now();
    render();
    auto duration = std::chrono::high_resolution_clock::now() - start;
    auto duration_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
#ifndef NODELAY
    if (durationInMilliseconds > 0) {
      Utility::wait(durationInMilliseconds / steps - duration_ms);
    }
#endif
#endif
  }
}

void Strip::fillAll(Color *colors, int durationInMilliseconds) {
  Linear t;
  fillAll(colors, durationInMilliseconds, t);
}
void Strip::fillAll(Color color, int durationInMilliseconds,
                    TimingFunction &fn) {
  Color colors[numberOfLeds];
  std::fill(colors, colors + numberOfLeds, color);
  fillAll(colors, durationInMilliseconds, fn);
}
void Strip::fillAll(Color color, int durationInMilliseconds) {
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

void Strip::fillAll(std::vector<Color> colors, int durationInMilliseconds,
                    TimingFunction &timing) {
  fillAll(&colors[0], durationInMilliseconds, timing);
}

void Strip::fillAll(std::vector<Color> colors) { fillAll(colors, 0); }

void Strip::fillAll(HSL *hsl, int durationInMilliseconds) {
  Color color[numberOfLeds];
  for (int i = 0; i < numberOfLeds; i++) {
    color[i] = Color::fromHSL(hsl[i]);
  }
  fillAll(color, durationInMilliseconds);
}
std::vector<Color> Strip::colors() {
  auto vec = std::vector<Color>(numberOfLeds);
  for (int i = 0; i < numberOfLeds; i++) {
    vec[i] = leds[i].color;
  }
  return vec;
}

void Strip::fillAll(Gradient gradient, int durationInMilliseconds) {
  this->fillAll(gradient.gradient_colors(this->numberOfLeds),
                durationInMilliseconds);
}
void Strip::fillAll(Gradient gradient) { fillAll(gradient, 0); }
