#include "LedState.h"
uint32_t LedState::toInteger() {
  Color c = this->color;
  return 0xff << 24 | c.red << 16 | c.green << 8 | c.blue;
}
