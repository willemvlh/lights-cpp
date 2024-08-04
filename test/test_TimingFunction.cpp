#include "TimingFunction.h"
#include "doctest.h"

TEST_CASE("linear") {
  Linear linear;
  CHECK_EQ(1, linear(1, 10));
  CHECK_EQ(2, linear(2, 10));
  CHECK_EQ(3, linear(3, 10));
}

TEST_CASE("ease in") {
  EaseIn easeIn(1.0);
  CHECK_EQ(1, easeIn(10, 100));
  CHECK_EQ(25, easeIn(50, 100));
  easeIn = EaseIn(2.0);
  CHECK_EQ(1, easeIn(20, 100));
}
TEST_CASE("ease out") {
  EaseOut easeOut(1.0);
  CHECK_EQ(1, easeOut(10, 100));
  CHECK_EQ(25, easeOut(50, 100));
  easeOut = EaseIn(2.0);
  CHECK_EQ(1, easeOut(20, 100));
}
