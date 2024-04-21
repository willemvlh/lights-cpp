#include "LedStrip.h"
#include "util.h"
#include <assert.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

int main() {
  LedStrip *strip = new LedStrip(30);
  strip->fillAll(0);
  Utility::waitFor(1000);
  strip->fillAll(Color{0x33,0,0}, 500); 
  delete strip;
  return 0;
}
