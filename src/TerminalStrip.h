#pragma once
#include "Strip.h"
class TerminalStrip : public Strip {
public:
  TerminalStrip(int leds) : Strip(leds){};
  void render() override;
};
