#include "Gradient.h"
#include "InterpolationCache.h"

std::vector<Color> Gradient::gradient_colors(int length) {
  std::vector<Color> vec;
  vec.reserve(length);
  InterpolationCache cache = InterpolationCache::current();
  auto iter = vec.begin();
  for (size_t i = 0; i < _colors.size() - 1; i++) {
    auto range = cache.get(_colors[i], _colors[i + 1],
                           (length / (_colors.size() - 1) - 1));
    vec.insert(iter, range.begin(), range.end());
    iter += range.size();
  }
  return vec;

}
Gradient::Gradient(std::vector<HSL> colors){
    auto col = std::vector<Color>(colors.size());
    for (size_t x = 0; x < colors.size(); ++x) {
        col[x] = Color::fromHSL(colors[x]);
    }
    this->_colors = col;
}


std::vector<Color> Gradient::colors(){
    return this->_colors;
}

