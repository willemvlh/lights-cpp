#ifndef LEDSTATE_H
#define LEDSTATE_H
#include <bits/stdint-uintn.h>
struct Color {
  char red;
  char green;
  char blue;
};
class LedState {
public:
  Color color;
  uint32_t toInteger();
};
#endif
