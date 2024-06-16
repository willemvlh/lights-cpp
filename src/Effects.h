#pragma once

#include "LedStrip.h"
class Effects {
private:
    LedStrip* _strip;
    void shift_saturation(float factor);
 public:
     Effects(LedStrip* strip);
     void rainbow(uint iterations);
};
