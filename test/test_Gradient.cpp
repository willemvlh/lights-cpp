#include "doctest.h"
#include "Gradient.h"

TEST_CASE("Gradient::gradient_colors") {
  Gradient red_yellow {std::vector<Color>{Color::Red, Color::Yellow}};
  auto colors = red_yellow.gradient_colors(3);
  CHECK_EQ(3, colors.size());
  CHECK_EQ(Color::Red, colors[0]);
  CHECK_EQ(Color::Yellow + Color::Red, colors[1]);
  CHECK_EQ(Color::Yellow, colors[2]);
}
