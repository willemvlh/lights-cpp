#pragma once

#import "Color.h"
#include <vector>

class Gradient {
private:
  std::vector<Color> _colors;

public:
  Gradient(std::vector<Color> colors) : _colors(colors) {}
  Gradient(std::vector<HSL> colors);
  std::vector<Color> gradient_colors(int length);
  std::vector<Color> colors();
};
