#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <thread>
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
} // namespace Utility
