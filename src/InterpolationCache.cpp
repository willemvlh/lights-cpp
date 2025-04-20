#include "InterpolationCache.h"
#include "Logger.h"
#include <cstdint>
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
  auto it = this->interpolationLookup.find(key);
  if (it != this->interpolationLookup.end()) {
    // lookup was found, move node to the front
    interpolationLookupList.splice(interpolationLookupList.begin(),
                                   interpolationLookupList, it->second);
    return it->second->second;
  } else {
    _cacheMisses++;
    auto interp = from.interpolate(to, steps);
    interpolationLookupList.emplace_front(
        key, interp); // new lookup, put it in the front of the list
    this->interpolationLookup[key] =
        interpolationLookupList.begin(); // and add it to the cache
    if (_cacheQueries % 1000 && isFull()) {
      Logger::log("Cache size exceeded", Debug);
      Logger::log("Current size: " + std::to_string(this->sizeBytes()), Debug);
      prune(maxSizeBytes / 2);
      Logger::log("New size: " + std::to_string(this->sizeBytes()), Debug);
      Logger::log("Cache queries: " + std::to_string(_cacheQueries), Debug);
    }
    return this->interpolationLookup[key]->second;
  }
}

void InterpolationCache::prune(size_t new_size) {
  size_t current_size = sizeBytes();
  while (current_size > new_size) {
    auto back = interpolationLookupList.back();
    size_t removed_size = this->cacheEntrySize(back.second);
    interpolationLookupList.pop_back();
    interpolationLookup.erase(back.first);
    current_size -= removed_size;
  }
}

InterpolationCache::InterpolationCache()
    : interpolationLookup(10000), interpolationLookupList(10000) {};

float InterpolationCache::cacheHitRatio() {
  if (_cacheQueries == 0)
    return 0;
  return 1 -
         static_cast<float>(_cacheMisses) / static_cast<float>(_cacheQueries);
}

size_t InterpolationCache::size() { return interpolationLookup.size(); }
uint64_t InterpolationCache::cacheMisses() { return _cacheMisses; }
uint64_t InterpolationCache::cacheHits() {
  return _cacheQueries - _cacheMisses;
}
