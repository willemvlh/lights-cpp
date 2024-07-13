#include "Effects.h"
#include "InterpolationCache.h"
#include "LedStrip.h"
#include "TimingFunction.h"
#include "util.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cwchar>
#include <iostream>
#include <sys/types.h>

Effects::Effects(Strip *strip) : _strip(strip) {}

template <typename T> void shiftArrayLeft(T *arr, size_t sz) {
  for (size_t i = 0; i < sz - 1; i++) {
    T current = arr[i];
    int next = i == sz - 1 ? 0 : i + 1;
    arr[i] = arr[next];
    arr[next] = current;
  }
}

template <typename T> void shiftArrayRight(T *arr, size_t sz) {
  T prev;
  T current;
  for (size_t i = 0; i < sz; i++) {
    current = arr[i];
    arr[i] = i == 0 ? arr[sz - 1] : prev;
    prev = current;
  }
}

void shiftHue(Color *colors, size_t sz, char by) {
  for (size_t i = 0; i < sz; i++) {
    auto hsl = colors[i].toHSL();
    hsl.hue += by;
    if (hsl.hue > 360.0) {
      hsl.hue -= 360.0;
    }
    colors[i] = Color::fromHSL(hsl);
  }
}

template <typename T> T normalize(T value, T range_min, T range_max) {
  return value * (range_max - range_min) + range_min;
}

void Effects::gradient(std::vector<Color> colors, int iterations) {
  auto cache = InterpolationCache();
  std::vector<Color> vec;
  vec.reserve(_strip->numberOfLeds);
  auto iter = vec.begin();
  for (size_t i = 0; i < colors.size() - 1; i++) {
    auto range = cache.get(colors[i], colors[i + 1],
                           (_strip->numberOfLeds / (colors.size() - 1) - 1));
    vec.insert(iter, range.begin(), range.end());
    iter += range.size();
  }
  for (int i = 0; i < iterations; i++) {
    _strip->fillAll(vec, 10000);
    shiftHue(&colors[0], _strip->numberOfLeds, 5);
  }
}

void Effects::wheel(int iterations, bool reverse = false) {
  int direction = reverse ? -1 : 1;
  for (int iter = 0; iter < iterations; ++iter) {
    for (int shift = 0; shift < _strip->numberOfLeds; ++shift) {
      std::vector<Color> colors;
      for (int i = 0; i < _strip->numberOfLeds; i++) {
        float hue =
            normalize(1.0 / _strip->numberOfLeds *
                          ((i + shift * direction) % _strip->numberOfLeds),
                      0.0, 360.0);
        colors.push_back(Color::fromHSL({hue, 0.5, 0.5}));
      }
      _strip->fillAll(colors, 500);
    }
  }
}

void Effects::shift() {
  float hue = 0.0;
  Color start = Color::fromHSL({hue, 0.5, 0.5});
  while (1) {
    EaseOut e;
    _strip->fillAll(start, 10000, e);
    Utility::waitFor(5000);
    start.setHSL(hue = Utility::wrapHue(hue + 60.0), 0.5, 0.5);
  }
}

void Effects::shiftGradient() {
  Color start{255, 0, 0};
  Color end;
  EaseOut timing;
  auto cache = InterpolationCache();
  while (1) {
    end = start.addHue(Utility::rand_between(31.0, 75.0));
    std::vector<Color> colors = cache.get(start, end, _strip->numberOfLeds);
    _strip->fillAll(colors, 3000);
    _strip->fillAll(end, 5000, timing);
    start = end;
  }
}
