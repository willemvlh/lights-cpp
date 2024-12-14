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

TEST_CASE("Gradient from HSL") {
    Gradient gr {std::vector<HSL>{{0,0,0}}};
    CHECK_EQ(Color::Black, gr.colors()[0]);
}

TEST_CASE("routine5") {
    auto colors = std::vector<HSL>{HSL{356,0.82,0.55}, HSL{23,0.6,0.82}, HSL{49,1.0,0.91}};
    Gradient gradient(colors);
    auto gr_colors = gradient.gradient_colors(60);
    CHECK_EQ(Color::fromHSL({356,0.82,0.55}), gr_colors[0]);
}
