#include "catch.hpp"
#include "LensSystem.h"

TEST_CASE("Lens::intersect") {
  SECTION("should intersect") {
    Lens lens(35.98738, 1.21638, 1.54, 23.716);

    lens.intersect({0,0,0},{0,0,0});
  }
}