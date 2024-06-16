#pragma once
#include <bits/stdint-uintn.h>
#include <ostream>
#include <sys/types.h>
#include <vector>
struct HSL {
  float hue;
  float saturation;
  float lightness;
};
class Color {
public:
  static Color fromHSL(HSL hsl);

  unsigned char red;
  unsigned char green;
  unsigned char blue;

  void setHSL(float,float,float);
  void setRGB(unsigned char, unsigned char, unsigned char);

  void lighten(float);
  void saturate(float);
  
  uint32_t toInteger() const;
  HSL toHSL() const;
  std::vector<Color> interpolate(Color to, int steps);
  //operators
  friend std::ostream &operator<<(std::ostream &os, const Color &color);
  bool operator==(const Color &color) const;
};

