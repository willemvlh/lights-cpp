#include "util.h"
#include "doctest.h"

TEST_CASE("Util::wrapHue") {
    CHECK_EQ(10.0, Utility::wrapHue(370.0));
}

TEST_CASE("Util::shiftArrayLeft"){
    auto vec = std::vector<int>{1,2,3};
    Utility::shiftArrayLeft(vec);
    CHECK_EQ(2, vec[0]);
    CHECK_EQ(3, vec[1]);
    CHECK_EQ(1, vec[2]);
    Utility::shiftArrayLeft(vec);
    Utility::shiftArrayLeft(vec);
    CHECK_EQ(1, vec[0]);
    CHECK_EQ(2, vec[1]);
    CHECK_EQ(3, vec[2]);
}


TEST_CASE("Util::divide_blocks") {
    auto colors = std::vector<Color>{Color::Red, Color::Green, Color::Blue};
    auto blocks = Utility::divide_blocks(colors, 9);
    CHECK_EQ(9, blocks.size());
    CHECK_EQ(Color::Red, blocks[0]);
    CHECK_EQ(Color::Red, blocks[1]);
    CHECK_EQ(Color::Red, blocks[2]);
    CHECK_EQ(Color::Green, blocks[3]);
    CHECK_EQ(Color::Green, blocks[4]);
    CHECK_EQ(Color::Green, blocks[5]);
    CHECK_EQ(Color::Blue, blocks[6]);
    CHECK_EQ(Color::Blue, blocks[7]);
    CHECK_EQ(Color::Blue, blocks[8]);
}
