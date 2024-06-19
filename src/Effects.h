#pragma once

#include "Strip.h"
class Effects {
private:
    Strip* _strip;
    void shift_saturation(float factor);
 public:
     Effects(Strip* strip);
     void rainbow(uint iterations);
};
