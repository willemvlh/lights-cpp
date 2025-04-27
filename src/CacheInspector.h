#pragma once

#include "InterpolationCache.h"

class CacheInspector {
private:
  const InterpolationCache &cache;

public:
  CacheInspector(const InterpolationCache &cache) : cache(cache) {}
  CacheInspector() = delete;
  const void report();
};
