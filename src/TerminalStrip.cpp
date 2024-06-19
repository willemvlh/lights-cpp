#include "TerminalStrip.h"
#include <algorithm>
#include <cstdio>
#include <iostream>

void TerminalStrip::render() {
  for (int i = 0; i < this->numberOfLeds; i++) {
    auto color = leds[i].color;
    printf("\033[48;2;%d;%d;%dm", color.red, color.green, color.blue);
    printf(" \033[0m");
  }
  printf("\r");
}
