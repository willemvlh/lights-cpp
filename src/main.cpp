#include "Effects.h"
#include "LedStrip.h"
#include "TerminalStrip.h"
#include "util.h"
#include <assert.h>
#include <chrono>
#include <ctime>
#include <cwchar>
#include <iostream>
#include <thread>

int main() {
  //LedStrip strip(30);
  TerminalStrip strip(30);
  Effects effects(&strip);
  effects.rainbow(500);
  return 0;
}
