#include "LedState.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "LedStrip.h"
#include "doctest.h"

TEST_CASE("LedState::ToInteger") {
    auto led = new LedState();
    led->color = {0x33, 0x22, 0x11};
    CHECK(led->toInteger() == 0xff332211);
}

TEST_CASE("LedStrip::interpolate"){
   Color from = Color{0,0,0};
   Color to = Color{255,0,0};
   auto result = from.interpolate(to, 10);
   CHECK(result.size() == 10);
   CHECK(result.begin()->red == 0);
   CHECK(result[0].red == 0);
   CHECK(result[9].red == 255);
}
