#ifndef LEDSTATE_H
#define LEDSTATE_H
#include <bits/c++config.h>
#include <bits/stdint-uintn.h>
#include <ostream>
#include <unordered_map>
#include <utility>
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

class LedState {
public:
  Color color;
  uint32_t toInteger();
};

struct ColorHash{
    std::size_t operator()(const Color& color) const {
        return color.red ^ color.green ^ color.blue;
    }
};


struct ColorPairHash{
  std::size_t operator()(const std::pair<Color, Color> pair) const {
      return ColorHash()(pair.first) ^ ColorHash()(pair.second);
  }
};

#endif
