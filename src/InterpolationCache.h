#pragma once
#include "Color.h"
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

class CacheInspector; // forward declaration
                      //
enum InterpolationType { LINEAR, HUE };

class InterpolationCache {
  using ListIt = std::list<std::pair<uint64_t, std::vector<Color>>>::iterator;

private:
  std::unordered_map<uint64_t, ListIt> interpolationLookup;
  std::list<std::pair<uint64_t, std::vector<Color>>> interpolationLookupList;
  uint64_t _cacheQueries = 0;
  uint64_t _cacheMisses = 0;
  static std::unique_ptr<InterpolationCache> theInstance;
  InterpolationCache(const InterpolationCache &) = delete;
  size_t maxSizeBytes = 50000000; // 50M
  size_t cacheEntrySize(std::vector<Color> &vec) {
    return vec.capacity() * sizeof(Color) + sizeof(vec);
  }
  size_t _sizeBytes = 0;

public:
  InterpolationCache();
  std::vector<Color> get(Color from, Color to, uint16_t steps);
  static InterpolationCache &current();
  InterpolationType interpolationType = LINEAR;
  float cacheHitRatio() const;
  uint64_t cacheHits() const;
  uint64_t cacheMisses() const;
  size_t size() const;
  size_t sizeBytes() const { return _sizeBytes; }
  const bool isFull() const { return _sizeBytes >= maxSizeBytes; }
  void prune(size_t);
};
