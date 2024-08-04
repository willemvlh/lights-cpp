#pragma once

#import "Color.h"
#include <vector>

class Gradient {
private:
  std::vector<Color> colors;

public:
  Gradient(std::vector<Color> colors) : colors(colors) {}
  std::vector<Color> gradient_colors(int length);
};
