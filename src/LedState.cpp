#include "LedState.h"
#include <cmath>
#include <ios>
#include <iostream>
#include <ostream>
#include <vector>
uint32_t LedState::toInteger() { return this->color.toInteger(); }

uint32_t Color::toInteger() const {
  return 0xff << 24 | this->red << 16 | this->green << 8 | this->blue;
}

std::ostream &operator<<(std::ostream &os, const Color &obj) {
  os << std::hex;
  os << obj.toInteger();
  os << std::dec;
  return os;
};

bool Color::operator==(const Color &color) const {
  return this->red == color.red && this->green == color.green &&
         this->blue == color.blue;
}

