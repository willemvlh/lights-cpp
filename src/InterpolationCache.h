#pragma once
#include "Color.h"
#include <list>
#include <unordered_map>
#include <vector>

class InterpolationCache {
  using ListIt = std::list<std::pair<uint64_t, std::vector<Color>>>::iterator;

private:
  std::unordered_map<uint64_t, ListIt> cache;
  std::list<std::pair<uint64_t, std::vector<Color>>> colors;
  uint64_t _cacheQueries = 0;
  uint64_t _cacheMisses = 0;
  static InterpolationCache &theInstance;
  InterpolationCache();

public:
  std::vector<Color> get(Color from, Color to, uint16_t steps);
  static InterpolationCache &current();
  float cacheHitRatio();
  uint64_t cacheHits();
  uint64_t cacheMisses();
  size_t size();
};
