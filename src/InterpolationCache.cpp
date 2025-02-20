#include "InterpolationCache.h"
#include <vector>

InterpolationCache& InterpolationCache::current(){
    static InterpolationCache instance;
    return instance;
}

std::vector<Color> InterpolationCache::get(Color from, Color to, uint16_t steps) {
  uint64_t key;
  key = static_cast<uint64_t>(from.toInteger() & 0x00ffffff) << 32; 
  key = (key | to.toInteger()) << 16;
  key = key | steps; 
  auto value = this->cache.find(key);
  if (value == this->cache.end()) {
    auto interp = from.interpolate(to, steps);
    if (this->cache.size() < 100000) {
      this->cache[key] = interp;
    }
    return this->cache[key];
  }
  return value->second;
}

InterpolationCache::InterpolationCache() : cache(10000){};
