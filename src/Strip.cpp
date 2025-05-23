#include "Strip.h"
#include "InterpolationCache.h"
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
    this->leds[i] = LedState{Color{0, 0, 0}};
  }
}
Strip::~Strip() { delete[] this->leds; };

int numberOfSteps(int durationInMilliseconds) {
  return std::max(1, durationInMilliseconds / 10);
}

void Strip::fillAll(Color *colors, int durationInMilliseconds,
                    const TimingFunction &fn) {
  int steps = numberOfSteps(durationInMilliseconds);
  auto interpolations = std::vector<std::vector<Color>>(numberOfLeds);
  for (int i = 0; i < numberOfLeds; i++) {
    interpolations[i] =
        InterpolationCache::current().get(leds[i].color, colors[i], steps);
  }
  for (int step = 0; step < steps; step++) {
    for (int i = 0; i < numberOfLeds; i++) {
      int timingAdaptedStep = fn(step, steps);
      leds[i].setColor(
          interpolations[i][timingAdaptedStep +
                            1]); // interpolation includes starting color,
                                 // which we skip by doing step+1
    }
    auto start = std::chrono::high_resolution_clock::now();
    if (shouldRender)
      render();
    auto duration = std::chrono::high_resolution_clock::now() - start;
    auto duration_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    if (durationInMilliseconds > 0 && shouldWait) {
      Utility::wait(durationInMilliseconds / steps - duration_ms);
    }
  }
}

void Strip::fillAll(Color *colors, int durationInMilliseconds) {
  Linear t;
  fillAll(colors, durationInMilliseconds, t);
}
void Strip::fillAll(Color color, int durationInMilliseconds,
                    const TimingFunction &fn) {
  std::vector<Color> colors(numberOfLeds, color);
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
                    const TimingFunction &timing) {
  fillAll(&colors[0], durationInMilliseconds, timing);
}

void Strip::fillAll(std::vector<Color> colors) { fillAll(colors, 0); }

void Strip::fillAll(HSL *hsl, int durationInMilliseconds) {
  std::vector<Color> colors(numberOfLeds);
  for (int i = 0; i < numberOfLeds; i++) {
    colors[i] = Color::fromHSL(hsl[i]);
  }
  fillAll(colors, durationInMilliseconds);
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

void Strip::setRender(bool b) { shouldRender = b; }
void Strip::setDelay(bool b) { shouldWait = b; }
