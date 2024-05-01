#ifndef INTERPOL_CACHE_H
#define INTERPOL_CACHE_H
#include "LedState.h"
#include <vector>
class InterpolationCache {
private:
  std::unordered_map<std::pair<Color, Color>, std::vector<Color>, ColorPairHash>
      cache;

public:
  std::vector<Color> *get(Color from, Color to);
  InterpolationCache();
};
#endif
