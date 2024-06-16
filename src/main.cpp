#include "Effects.h"
#include "LedStrip.h"
#include "util.h"
#include <assert.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

int main() {
  LedStrip strip(30);
  Effects effects(&strip);
  effects.rainbow(500000);
  return 0;
}
