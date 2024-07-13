#include "Color.h"
#include "InterpolationCache.h"
#include "doctest.h"

TEST_CASE("Color::toInteger") {
  auto red = Color{0xff, 0, 0};
  CHECK_EQ(0xffff0000, red.toInteger());
}

TEST_CASE("ffff00fd::toHSL") {
  auto color = Color{0xff, 0, 0xfd};
  CHECK(color.toHSL().hue >= 0);
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
  CHECK(Color::fromHSL(color.toHSL()) == color);
}

TEST_CASE("Color::addHue") {
    Color color = Color::fromHSL({300.0, 0, 0});
    CHECK_EQ(300.0, color.toHSL().hue);
    auto color2 = color.addHue(50.0);
    CHECK_EQ(350.0, color2.toHSL().hue);
}
