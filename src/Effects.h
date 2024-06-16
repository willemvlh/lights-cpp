#pragma once

#include "LedStrip.h"
class Effects {
private:
    LedStrip* _strip;
 public:
     Effects(LedStrip* strip);
     void rainbow(int durationInMilliseconds);
};
