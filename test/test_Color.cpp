#include "Color.h"
#include "InterpolationCache.h"
#include "doctest.h"

TEST_CASE("Color::toInteger") {
  auto red = Color{0xff, 0, 0};
  CHECK_EQ(0xffff0000, red.toInteger());
}

TEST_CASE("Color::toHSL") {
  auto red = Color{0xff, 0, 0};
  auto hsl = red.toHSL();
  CHECK_EQ(0.0, hsl.hue);
  CHECK_EQ(1.0, hsl.saturation);
  CHECK_EQ(0.5, hsl.lightness);

  auto blueish = Color{0, 0xff, 0xfb}.toHSL();
  CHECK_EQ(179, (int)blueish.hue);
  CHECK_EQ(1.0, blueish.saturation);
  CHECK_EQ(0.5, blueish.lightness);

  auto darkyellow = Color{115, 109, 60}.toHSL();
  CAPTURE(darkyellow.saturation);
  CAPTURE(darkyellow.lightness);
  CHECK_EQ(53, (int)darkyellow.hue);
  CHECK(0.31 < darkyellow.saturation);
  CHECK(darkyellow.saturation < 0.33);
  CHECK(0.34 < darkyellow.lightness);
  CHECK(darkyellow.lightness < 0.35);
}

TEST_CASE("Color::fromHSL") {
  Color color = {255, 0, 0};
  CHECK(Color::fromHSL(color.toHSL()) == color);
  color = Color{0, 255, 0};
  CHECK(Color::fromHSL(color.toHSL()) == color);
  color = Color{0, 0, 255};
  CHECK(Color::fromHSL(color.toHSL()) == color);
  color = Color{123, 213, 99};
  CAPTURE(color.toHSL().hue);
  CAPTURE(color.toHSL().saturation);
  CAPTURE(color.toHSL().lightness);
  CHECK(Color::fromHSL(color.toHSL()) == color);
}

TEST_CASE("InterpolationCache") {
  auto cache = InterpolationCache();
  auto white = Color{0xff, 0xff, 0xff};
  auto black = Color{0, 0, 0};
  std::vector<Color> *result = cache.get(black, white, 10);
  CHECK_EQ(10, result->size());
}
