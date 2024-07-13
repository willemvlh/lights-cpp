#pragma once

#include "Strip.h"
class Effects {
private:
    Strip* _strip;
 public:
     Effects(Strip* strip);
     void gradient(std::vector<Color>, int iterations);
     void wheel(int iterations, bool reverse);
     void shift();
     void shiftGradient();
};
