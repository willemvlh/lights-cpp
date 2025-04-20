#include "InterpolationCache.h"
#include "doctest.h"

typedef std::vector<std::vector<Color>> Interpolation;

TEST_CASE("InterpolationCache") {
  auto cache = InterpolationCache::current();
  cache.clear();
  CHECK_EQ(0, cache.size());
  auto c = cache.get(Color::Red, Color::Green, 12);
  CHECK_EQ(1, cache.size());
  CHECK_EQ(1, cache.cacheMisses());
  auto col = Color::Red;
  auto interp = (col.interpolate(Color::Green, 12), c);
  CHECK_EQ(interp.size(), c.size());
  c = cache.get(Color::Red, Color::Green, 12);
  CHECK_EQ(1, cache.cacheMisses());
  CHECK_EQ(c, interp);
}

TEST_CASE("size") {
  auto cache = InterpolationCache::current();
  cache.clear();
  CHECK_EQ(0, cache.size());
  CHECK_EQ(0, cache.sizeBytes());
  auto vec = cache.get(Color::Red, Color::Green, 1);
  CHECK_EQ(2, vec.size());
  CHECK_EQ(16 + sizeof(std::vector<Color>), cache.sizeBytes());
  cache.get(Color::Red, Color::Green, 1);
  CHECK_EQ(2 * sizeof(Color) + sizeof(Interpolation), cache.sizeBytes());
  cache.clear();
  vec = cache.get(Color::Green, Color::Red, 10);
  CHECK_EQ(11, vec.size());
  CHECK_EQ(11 * sizeof(Color) + sizeof(Interpolation), cache.sizeBytes());
  CHECK_FALSE(cache.isFull());
}


TEST_CASE("prune"){
  auto cache = InterpolationCache::current();
  cache.clear();
  cache.get(Color::Red, Color::Green, 1);
  cache.get(Color::Orange, Color::Green, 1);
  auto interm_size = cache.sizeBytes();
  cache.get(Color::Yellow, Color::Green, 1);
  CHECK_EQ(3, cache.size());
  cache.prune(interm_size);
  CHECK_EQ(2, cache.size());
  cache.get(Color::Red, Color::Green, 1);
  CHECK_EQ(3, cache.size());
}
