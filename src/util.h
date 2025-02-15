#include "Color.h"
#include <cmath>
#include <vector>
#pragma once

#define ASSERT_MSG(condition, msg)                                             \
  do {                                                                         \
    if (!(condition)) {                                                        \
      std::cerr << "Assertion failed: (" #condition "), "                      \
                << "function " << __FUNCTION__ << ", "                         \
                << "file " << __FILE__ << ", "                                 \
                << "line " << __LINE__ << ": " << msg << std::endl;            \
      std::abort();                                                            \
    }                                                                          \
  } while (false)

namespace Utility {
void wait(int milliseconds);
float wrapHue(float hue);
char *readEnv(const char *envVar, const char *_default);
float rand_between(float min, float max);

std::vector<Color> divide_blocks(std::vector<Color>, size_t size);

template <typename T> void shiftArrayLeft(std::vector<T> &arr) {
  for (size_t i = 0; i < arr.size() - 1; i++) {
    T current = arr[i];
    int next = i == arr.size() - 1 ? 0 : i + 1;
    arr[i] = arr[next];
    arr[next] = current;
  }
}

/*
 *[4,3,9,1]
 4

 * */

template <typename T> void shiftArrayRight(std::vector<T> &arr) {
  T prev;
  T current;
  for (size_t i = 0; i < arr.size(); i++) {
    current = arr[i];
    arr[i] = i == 0 ? arr[arr.size() - 1] : prev;
    prev = current;
  }
}
} // namespace Utility
