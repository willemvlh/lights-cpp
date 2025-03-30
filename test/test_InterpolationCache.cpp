#include "InterpolationCache.h"
#include "doctest.h"

TEST_CASE("InterpolationCache") {
  auto cache = InterpolationCache::current();
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
