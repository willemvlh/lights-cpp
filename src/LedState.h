#ifndef LEDSTATE_H
#define LEDSTATE_H
#include "Color.h"

struct ColorCorrection {
  float red = 1.0f;
  float green = 1.0f;
  float blue = 1.0f;
};

class LedState {
public:
  Color color;
  ColorCorrection correction{};
  uint32_t toInteger();
  void setColor(Color);
};

#endif
