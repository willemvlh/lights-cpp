#pragma once
#include "Color.h"
#include <unordered_map>
#include <vector>

class InterpolationCache {
private:
  std::unordered_map<uint64_t, std::vector<Color>> cache;

public:
  std::vector<Color> *get(Color from, Color to, uint16_t steps);
  InterpolationCache();
};
