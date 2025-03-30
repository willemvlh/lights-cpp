#include "InterpolationCache.h"
#include <cstdint>
#include <iostream>
#include <vector>

uint64_t getKey(Color from, Color to, uint16_t steps) {
  uint64_t key;
  key = static_cast<uint64_t>(from.toInteger() & 0x00ffffff) << 32;
  key = (key | to.toInteger()) << 16;
  key = key | steps;
  return key;
}

InterpolationCache &InterpolationCache::current() {
  static InterpolationCache instance;
  return instance;
}

std::vector<Color> InterpolationCache::get(Color from, Color to,
                                           uint16_t steps) {
  _cacheQueries++;
  auto key = getKey(from, to, steps);
  auto it = this->cache.find(key);
  if (it != this->cache.end()) {
    // lookup was found, move node to the front
    colors.splice(colors.begin(), colors, it->second);
    return it->second->second;
  } else {
    _cacheMisses++;
    auto interp = from.interpolate(to, steps);
    colors.emplace_front(key, interp); //new lookup, put it in the front
    this->cache[key] = colors.begin(); //also assign iterator to key 
    if (colors.size() > 10000) {
      auto lruKey = colors.back().first;
      cache.erase(lruKey);
      colors.pop_back();
    }
    return this->cache[key]->second;
  }
}

InterpolationCache::InterpolationCache() : cache(10000), colors(10000) {};

float InterpolationCache::cacheHitRatio() {
  if (_cacheQueries == 0)
    return 0;
  return 1 - static_cast<float>(_cacheMisses) / (_cacheQueries);
}

size_t InterpolationCache::size() { return cache.size(); }
uint64_t InterpolationCache::cacheMisses() { return _cacheMisses; }
uint64_t InterpolationCache::cacheHits() {
  return _cacheQueries - _cacheMisses;
}
