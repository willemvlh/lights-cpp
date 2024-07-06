#pragma once

#include "Strip.h"
class Effects {
private:
    Strip* _strip;
 public:
     Effects(Strip* strip);
     void gradient(Color color1, Color color2, int iterations);
     void wheel(int iterations, bool reverse);
};
