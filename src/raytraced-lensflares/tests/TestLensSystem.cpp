#include "LensSystem.h"
#include "catch.hpp"
/*
TEST_CASE("LensData::intersect") {
  SECTION("should intersect") {
    LensData lens(35.98738, 1.21638, 1.54, 23.716);

    //lens.intersect({0,0,0},{0,0,0});
  }
}*/

TEST_CASE("LensSystem") {
  SECTION("should calculate lens centers correctly") {
    LensSystem lensSystem("test", {{{40.93, 10.64, 1, 17.3},
                                    {183.92, 7.05, 1.6910, 16.5},
                                    {-48.91, 79.831, 1, 16.5}}});

    REQUIRE(lensSystem.lenses[0].center == Catch::Detail::Approx(86.8810043));
    REQUIRE(lensSystem.lenses[1].center == Catch::Detail::Approx(79.8310013f));
    REQUIRE(lensSystem.lenses[2].center == 0);
  }
}