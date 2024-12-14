#pragma once
#include "Strip.h"

#if CAN_USE_STRIP
  #include "ws2811/ws2811.h"

class LedStrip : public Strip {
public:
    LedStrip(int leds);
    ~LedStrip();
private:
  ws2811_t strip;
  void syncLedState();
  void render() override;
};

#else
class LedStrip : public Strip {
public:
    LedStrip(int leds);
    ~LedStrip();
};
#endif