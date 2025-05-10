#include "LedState.h"
uint32_t LedState::toInteger() { return this->color.toInteger(); }

void LedState::setColor(Color color){
  auto [red,green,blue] = this->correction;
  u_char r = color.red * red;
  u_char g = color.green * green;
  u_char b = color.blue * blue;
  this->color =  color;
}


