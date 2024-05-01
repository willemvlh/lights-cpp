#ifndef COLOR_H
#define COLOR_H
#include <bits/stdint-uintn.h>
#include <ostream>
#include <vector>
class Color {
public:
  char red;
  char green;
  char blue;
  uint32_t toInteger() const;
  friend std::ostream &operator<<(std::ostream &os, const Color &color);
  bool operator==(const Color &color) const;
  std::vector<Color> interpolate(Color to, int steps);
};
#endif
