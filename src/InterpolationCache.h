#pragma once
#include "Color.h"
#include <list>
#include <unordered_map>
#include <vector>

class InterpolationCache {
  using ListIt = std::list<std::pair<uint64_t, std::vector<Color>>>::iterator;

private:
  std::unordered_map<uint64_t, ListIt> interpolationLookup;
  std::list<std::pair<uint64_t, std::vector<Color>>> interpolationLookupList;
  uint64_t _cacheQueries = 0;
  uint64_t _cacheMisses = 0;
  static InterpolationCache &theInstance;
  InterpolationCache();
  size_t maxSizeBytes = 50000000; // 50M
  size_t cacheEntrySize(std::vector<Color> &vec) {
    return vec.capacity() * sizeof(Color) + sizeof(vec);
  }

public:
  std::vector<Color> get(Color from, Color to, uint16_t steps);
  static InterpolationCache &current();
  float cacheHitRatio();
  uint64_t cacheHits();
  uint64_t cacheMisses();
  size_t size();
  size_t sizeBytes() {
    size_t size = 0;
    for (auto &pair : interpolationLookupList) {
      size += this->cacheEntrySize(pair.second);
    }
    return size;
  }
  bool isFull() {
    size_t size = 0;
    for (auto &pair : interpolationLookupList) {
      if (size >= maxSizeBytes) {
        return true;
      }
      size += this->cacheEntrySize(pair.second);
    }
    return false;
  }
  void prune(size_t);
  void clear() {
    interpolationLookup.clear();
    interpolationLookupList.clear();
  }
};
