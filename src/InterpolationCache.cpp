#include "InterpolationCache.h"
#include "LedState.h"
#include <vector>

std::vector<Color> *InterpolationCache::get(Color from, Color to, int steps) {
  auto pair = std::pair<Color, Color>(from, to);
  auto value = this->cache.find(pair);
  if (value == this->cache.end()) {
    auto interp = from.interpolate(to, steps);
    if (this->cache.size() < 100000) {
      this->cache[pair] = interp;
    }
    return &this->cache[pair];
  }
  return &value->second;
}

InterpolationCache::InterpolationCache() : cache(10000){};
