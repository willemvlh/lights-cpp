#include "Color.h"
#include <algorithm>
#include <bits/stdint-uintn.h>
#include <cmath>
#include <cstdlib>
#include <initializer_list>
uint32_t Color::toInteger() const {
  return 0xff << 24 | this->red << 16 | this->green << 8 | this->blue;
}

Color Color::fromHSL(HSL hsl) {
  float h = std::fmod(hsl.hue, 360.0), s = hsl.saturation, l = hsl.lightness;
  auto chroma = (1 - std::abs(2. * l - 1)) * s;
  auto hue_prime = h / 60;
  auto x = chroma * (1 - std::abs(std::fmod(hue_prime, 2) - 1));
  float r, g, b;
  if (hue_prime >= 5) {
    r = chroma;
    g = 0;
    b = x;
  } else if (hue_prime >= 4) {
    r = x;
    g = 0;
    b = chroma;
  } else if (hue_prime >= 3) {
    r = 0;
    g = x;
    b = chroma;
  } else if (hue_prime >= 2) {
    r = 0;
    g = chroma;
    b = x;
  } else if (hue_prime >= 1) {
    r = x;
    g = chroma;
    b = 0;
  } else if (hue_prime >= 0) {
    r = chroma;
    g = x;
    b = 0;
  } else {
    r = 0;
    g = 0;
    b = 0;
  }
  float m = l - 0.5 * chroma;
  Color color;
  color.red = static_cast<int>((r + m) * 255);
  color.green = static_cast<int>((g + m) * 255);
  color.blue = static_cast<int>((b + m) * 255);
  return color;
}

HSL Color::toHSL() const {
  float r = this->red / 255.0;
  float g = this->green / 255.0;
  float b = this->blue / 255.0;
  std::initializer_list<float> arr = {r, g, b};
  auto minmax = std::minmax(arr);
  auto min = minmax.first;
  auto max = minmax.second;
  auto delta = max - min;
  float h, s, l;

  // hue
  if (delta == 0) {
    h = 0;
  } else if (max == r) {
    h = std::fmod((g - b) / delta, 6);
  } else if (max == g) {
    h = ((b - r) / delta) + 2;
  } else {
    h = ((r - g) / delta) + 4;
  }
  h *= 60.0;

  // lightness
  l = (max + min) / 2;

  // saturation
  s = delta == 0 ? 0 : delta / (1 - std::abs(2 * l - 1));
  return {h, s, l};
}

std::ostream &operator<<(std::ostream &os, const Color &obj) {
  os << std::hex;
  os << obj.toInteger();
  os << std::dec;
  return os;
};

bool Color::operator==(const Color &color) const {
  return this->red == color.red && this->green == color.green &&
         this->blue == color.blue;
}

void Color::setHSL(float hue, float sat, float lightness) {
  auto color = Color::fromHSL({hue, sat, lightness});
  this->red = color.red;
  this->green = color.green;
  this->blue = color.blue;
}

void Color::setRGB(unsigned char r, unsigned char g, unsigned char b) {
  this->red = r;
  this->green = g;
  this->blue = b;
}

void Color::lighten(float f) {
  auto hsl = this->toHSL();
  auto lightness = std::max(std::min(1.0f, hsl.lightness + f), 0.0f);
  this->setHSL(hsl.hue, hsl.saturation, lightness);
}
void Color::saturate(float f) {
  auto hsl = this->toHSL();
  auto sat = std::max(std::min(1.0f, hsl.saturation + f), 0.0f);
  this->setHSL(hsl.hue, sat, hsl.lightness);
}

std::vector<Color> Color::interpolate(Color to, int steps) {
  if (steps < 1) {
    throw std::invalid_argument("steps should be > 0");
  }
  float f_steps = static_cast<float>(steps);
  auto v = std::vector<Color>(steps + 1);
  v[0] = *this;
  float f_red = (to.red - this->red) / f_steps;
  float f_green = (to.green - this->green) / f_steps;
  float f_blue = (to.blue - this->blue) / f_steps;
  for (int i = 0; i < steps; i++) {
    char red = std::round(this->red + f_red * i);
    char green = std::round(this->green + f_green * i);
    char blue = std::round(this->blue + f_blue * i);
    Color c = {red, green, blue};
    v[i] = c;
  }
  v[steps] = to;
  return v;
}
