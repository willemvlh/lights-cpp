#ifndef INTERPOL_CACHE_H
#define INTERPOL_CACHE_H
#include "Color.h"
#include <vector>
#include <unordered_map>

struct ColorHash {
  std::size_t operator()(const Color &color) const {
    return color.red ^ color.green ^ color.blue;
  }
};

struct ColorPairHash {
  std::size_t operator()(const std::pair<Color, Color> pair) const {
    return ColorHash()(pair.first) ^ ColorHash()(pair.second);
  }
};
class InterpolationCache {
private:
  std::unordered_map<std::pair<Color, Color>, std::vector<Color>, ColorPairHash>
      cache;

public:
  std::vector<Color> *get(Color from, Color to, int steps);
  InterpolationCache();
};
#endif
