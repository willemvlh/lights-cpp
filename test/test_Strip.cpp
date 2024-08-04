#include "TerminalStrip.h"
#include "doctest.h"

TEST_CASE("colors"){
    TerminalStrip strip = TerminalStrip(5);
    strip.fillAll(Color::Red);
    auto colors = strip.colors();
    CHECK_EQ(5, colors.size());
    for(auto color : colors){
        CHECK_EQ(Color::Red, color);
    }
    for(auto& color : colors){
        color.saturate(-1.0);
    }
    for(auto color : colors){
        CHECK_EQ(0.0, color.toHSL().saturation);
    }

}
