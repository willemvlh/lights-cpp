#include "LedState.h"
#include "LedStrip.h"
#include "doctest.h"

TEST_CASE("LedState::ToInteger") {
  auto led = new LedState();
  led->color = {0x33, 0x22, 0x11};
  CHECK(led->toInteger() == 0xff332211);
}

TEST_CASE("LedStrip::interpolate") {
  Color from = Color{0, 0, 0};
  Color to = Color{200, 0, 0};
  auto result = from.interpolate(to, 2);
  CHECK(result.size() == 3);
  CHECK(result[0].red == 0);
  CHECK(result[1].red == 100);
  CHECK(result[2].red == 200);
}
