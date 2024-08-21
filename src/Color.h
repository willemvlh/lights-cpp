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
  /*By storing the hue, it is possible to completely darken or desaturate a color and restore it later*/

  float hue = -1.0;

  void setHSL(float, float, float);
  void setRGB(unsigned char, unsigned char, unsigned char);

  void lighten(float);
  void saturate(float);
  void setLightness(float);
  void setSaturation(float);
  uint32_t toInteger() const;
  HSL toHSL() const;

  Color addHue(float hue);
  std::vector<Color> interpolate(Color to, int steps);
  // operators
  friend std::ostream &operator<<(std::ostream &os, const Color &color);
   bool operator==(const Color &color) const;
  const Color operator+(const Color &color) const;

  static const Color Red;
  static const Color Green;
  static const Color Blue;
  static const Color Yellow;
  static const Color Cyan;
  static const Color Magenta;
  static const Color Black;
  static const Color White;
  static const Color Gray;
  static const Color Maroon;
  static const Color Olive;
  static const Color Lime;
  static const Color Teal;
  static const Color Navy;
  static const Color Fuchsia;
  static const Color Purple;
  static const Color Silver;
  static const Color Brown;
  static const Color Orange;
  static const Color Pink;
  static const Color Gold;
  static const Color LightGray;
  static const Color DarkGray;
  static const Color Beige;
  static const Color Coral;


  static Color random();
};
