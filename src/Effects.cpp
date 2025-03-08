#include "Effects.h"
#include "InterpolationCache.h"
#include "Palettes_generated.h"
#include "TimingFunction.h"
#include "util.h"
#include <cassert>
#include <cwchar>
#include <sys/types.h>

Effects::Effects(Strip *strip) : _strip(strip) {}

template <typename T> T normalize(T value, T range_min, T range_max) {
  return value * (range_max - range_min) + range_min;
}

void Effects::pulse(int durationsInMilliseconds, int iterations) {
  std::vector<Color> current = _strip->colors();
  std::vector<Color> darkened = _strip->colors();
  for (auto &color : darkened) {
    color.setLightness(0.3);
  }

  for (int i = 0; i < iterations; i++) {
    EaseIn in(2);
    EaseOut out(2);
    _strip->fillAll(darkened, durationsInMilliseconds / 2, in);
    _strip->fillAll(current, durationsInMilliseconds / 2, out);
  }
};

void Effects::palettes() {
  /*
   * This should probably refactored and moved to Show.cpp
   */
  size_t count;
  int speed = Utility::rand_between(30, 120);
  auto palettes = shuffled_palettes();
  for (auto &palette : palettes) {
    std::vector<Color> colors =
        Utility::divide_blocks(palette, _strip->numberOfLeds);
    for (size_t i = 0; i < 200; i++) {
      _strip->fillAll(colors, speed);
      Utility::shiftArrayLeft(colors);
    }
  }
}

/*
 * Like palettes, but without lateral movement, and with pulsing
 * */
void Effects::palettes_static() {
  size_t count;
  int speed = Utility::rand_between(500, 5000);
  auto palettes = shuffled_palettes();
  for (auto &palette : palettes) {
    std::vector<Color> colors =
        Utility::divide_blocks(palette, _strip->numberOfLeds);
    _strip->fillAll(colors, speed);
    this->pulse(2900, 12);
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
        if (hue < 0) {
          hue += 360.0;
        }
        colors.push_back(Color::fromHSL({hue, 0.7, 0.5}));
      }
      _strip->fillAll(colors, 100);
    }
  }
}

/*
 *Starts from full red. Then changes colors by 60deg in 5sec intervals
 * */
void Effects::shift() {
  float hue = 0.0;
  Color start = Color::fromHSL({hue, 0.5, 0.5});
  while (1) {
    EaseOut e(1.0);
    _strip->fillAll(start, 10000, e);
    Utility::wait(5000);
    start.setHSL(hue = Utility::wrapHue(hue + 60.0), 0.5, 0.5);
  }
}

void Effects::shiftGradient(int iterations) {
  Color start{255, 0, 0};
  Color end;
  EaseOut timing(1.0);
  auto cache = InterpolationCache::current();
  for (int i = 0; i < iterations; i++) {
    end = start.addHue(Utility::rand_between(31.0, 75.0));
    std::vector<Color> colors = cache.get(start, end, _strip->numberOfLeds);
    _strip->fillAll(colors, 3000);
    _strip->fillAll(end, 5000, timing);
    start = end;
  }
}
