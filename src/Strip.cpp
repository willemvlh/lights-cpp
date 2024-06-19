#include "Strip.h"
#include "LedState.h"
#include "util.h"
#include "ws2811.h"
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

void Strip::fillAll(Color *colors, int durationInMilliseconds) {
  int steps = durationInMilliseconds / 30;
  auto interpolations = std::vector<std::vector<Color>>(numberOfLeds);
  for (int i = 0; i < numberOfLeds; i++) {
    interpolations[i] = leds[i].color.interpolate(colors[i], steps);
  }
  for (int index = 0; index < steps; index++) {
    for (int i = 0; i < numberOfLeds; i++) {
      leds[i].color = interpolations[i][index];
    }
    auto start = std::chrono::high_resolution_clock::now();
    render();
    auto duration = std::chrono::high_resolution_clock::now() - start;
    auto duration_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    Utility::waitFor(durationInMilliseconds / steps - duration_ms);
  }
}

void Strip::fillAll(Color color, int durationInMilliseconds) {
  Color colors[numberOfLeds];
  std::fill(colors, colors + numberOfLeds, color);
  fillAll(colors, durationInMilliseconds);
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

void Strip::fillAll(HSL *hsl, int durationInMilliseconds) {
  Color color[numberOfLeds];
  for (int i = 0; i < numberOfLeds; i++) {
    color[i] = Color::fromHSL(hsl[i]);
  }
  fillAll(color, durationInMilliseconds);
}

std::vector<Color> Color::interpolate(Color to, int steps) {
  auto v = std::vector<Color>(steps);
  float f_red = (to.red - this->red) * (1.0 / (steps - 1));
  float f_green = (to.green - this->green) * (1.0 / (steps - 1));
  float f_blue = (to.blue - this->blue) * (1.0 / (steps - 1));
  for (int i = 0; i < steps; i++) {
    char red = std::round(this->red + f_red * i);
    char green = std::round(this->green + f_green * i);
    char blue = std::round(this->blue + f_blue * i);
    Color c = {red, green, blue};
    v[i] = c;
  }
  return v;
}
