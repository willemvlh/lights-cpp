#include "Show.h"
#include "Effects.h"
#include "Strip.h"
#include <algorithm>
#include <cstdlib>
void show(Strip *strip) {
  while (1) {
    auto x = std::rand() % 3;
    switch (x) {
    case 0:
      return routine1(strip);
    case 1:
      return routine2(strip);
    case 2:
      return routine3(strip);
    }
    return;
  }
}

  void routine1(Strip * strip) {
    auto color1 = Color::random();
    auto color2 = color1.addHue(60);
    auto interpolation = color1.interpolate(color2, strip->numberOfLeds);
    auto reversed = interpolation;
    std::reverse(reversed.begin(), reversed.end());
    EaseIn timing(1);
    for (int i = 0; i < 25; i++) {
      strip->fillAll(interpolation, 5000, timing);
      strip->fillAll(reversed, 5000, timing);
    }
  };

  void routine2(Strip * strip) {
    Effects eff(strip);
    eff.wheel(5, false);
    eff.wheel(10, true);
  }

  void routine3(Strip * strip) {
    Effects eff(strip);
    eff.shiftGradient(13);
  }
