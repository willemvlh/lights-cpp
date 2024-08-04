#include "Gradient.h"
#include "InterpolationCache.h"

std::vector<Color> Gradient::gradient_colors(int length) {
  std::vector<Color> vec;
  vec.reserve(length);
  InterpolationCache cache = InterpolationCache::current();
  auto iter = vec.begin();
  for (size_t i = 0; i < colors.size() - 1; i++) {
    auto range = cache.get(colors[i], colors[i + 1],
                           (length / (colors.size() - 1) - 1));
    vec.insert(iter, range.begin(), range.end());
    iter += range.size();
  }
  return vec;

}
