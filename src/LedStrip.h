#pragma once
#include "InterpolationCache.h"
#include "LedState.h"
#include "Strip.h"
#include "ws2811/ws2811.h"
#include <vector>

class LedStrip : public Strip {
public:
    LedStrip(int leds);
    ~LedStrip();
private:
  ws2811_t strip;
  void syncLedState();
  void render() override;
};
