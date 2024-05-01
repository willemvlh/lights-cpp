#include "LedStrip.h"
#include "util.h"
#include <assert.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

int main() {
  LedStrip *strip = new LedStrip(30);
  while (1) {
    strip->fillAll(Color{0xFF, 0xFF, 0xFF}, 4000); 
    Utility::waitFor(3000);
    strip->fillAll(Color{0x00, 0x00, 0x00}, 4000); 
  };
  delete strip;
  return 0;

}
