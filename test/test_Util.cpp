#include "util.h"
#include "doctest.h"

TEST_CASE("Util::wrapHue") {
    CHECK_EQ(10.0, Utility::wrapHue(370.0));
}

