#include "Effects.h"
#include "LedStrip.h"
#include <algorithm>
#include <chrono>
#include <cwchar>
#include <iostream>

Effects::Effects(LedStrip *strip) : _strip(strip) {}

template <typename T> void shiftArrayRight(T *arr, size_t sz) {
  T prev;
  T current;
  for (size_t i = 0; i < sz; i++) {
    current = arr[i];
    arr[i] = i == 0 ? arr[sz - 1] : prev;
    prev = current;
  }
}

void Effects::rainbow(uint iterations) {
  HSL colors[_strip->numberOfLeds];
  float numberOfLeds = _strip->numberOfLeds;
  for (int i = 1; i <= _strip->numberOfLeds; i++) {
    colors[i - 1] = {0xff * i / numberOfLeds, 0.5, 0.5};
  }
  uint counter = 0;
  while (counter < iterations) {
    counter++;
    float direction = 1;
    if (colors[0].saturation >= 0.95 || colors[0].saturation <= 0.25) {
      direction *= -1;
    }
    for(auto color: colors){
        color.saturation += 0.05 * direction;
    }
    for (int i = 0; i < numberOfLeds; i++) {
      _strip->fillAll(colors, 1000);
      shiftArrayRight(colors, numberOfLeds);
    }
  }
}
