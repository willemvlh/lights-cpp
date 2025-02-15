#include "Color.h"
#include "Constants.h"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <thread>
#include <vector>

namespace Utility {
void wait(int milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
float wrapHue(float hue) { return std::fmod(hue, 360.0); }

float rand_between(float min, float max) {
  float normalized = rand() / static_cast<float>(RAND_MAX);
  return min + normalized * (max - min);
}
const char *readEnv(const char *envVar, const char *_default) {
  const char *v = std::getenv(envVar);
  if (v) {
    return v;
  } else {
    return _default;
  }
}
std::vector<Color> divide_blocks(std::vector<Color> colors, size_t size) {
  std::vector<Color> vector;
  vector.reserve(size);
  size_t block_size = size / colors.size();
  for (auto color : colors) {
    for (size_t i = 0; i < block_size; i++) {
      vector.push_back(color);
    }
  }
  while (vector.size() < size) {
    vector.push_back(colors.back());
  }
  return vector;
}

} // namespace Utility
