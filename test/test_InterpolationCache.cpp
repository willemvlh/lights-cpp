#include "InterpolationCache.h"
#include "doctest.h"

TEST_CASE("Interpolation") {
  auto cache = InterpolationCache::current();
  CHECK_EQ(0, cache.size());
  auto c = cache.get(Color::Red, Color::Green, 12);
  CHECK_EQ(1, cache.size());
}
