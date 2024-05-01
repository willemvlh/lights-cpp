#ifndef LEDSTATE_H
#define LEDSTATE_H
#include "Color.h"

class LedState {
public:
  Color color;
  uint32_t toInteger();
};

#endif
