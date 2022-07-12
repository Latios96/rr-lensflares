#include "LensSystem.h"
#include "LensSystems.h"
#include "catch.hpp"

TEST_CASE("Lens::intersect") {
  SECTION("should intersect correctly with lens with positive radius") {
    auto testData = GENERATE(table<owl::vec3f, owl::vec3f, owl::vec3f>(
        {{{0, 0, -1}, {0, 0, 2}, {0, 0, 1}},
         {normalize(owl::vec3f(0, 1, -1)),
          {0, 1.0143f, 1.9857f},
          {0, 0.0281799994f, 0.9996f}}}));
    owl::vec3f direction = std::get<0>(testData);
    owl::vec3f position = std::get<1>(testData);
    owl::vec3f normal = std::get<2>(testData);

    Lens lens(35.98738, 1.21638, 1.54, 23.716, 2);

    Intersection intersection = lens.intersect({0, 0, 3}, direction);

    REQUIRE(intersection.position.x == Catch::Detail::Approx(position.x));
    REQUIRE(intersection.position.y == Catch::Detail::Approx(position.y));
    REQUIRE(intersection.position.z == Catch::Detail::Approx(position.z));

    REQUIRE(intersection.normal.x == Catch::Detail::Approx(normal.x));
    REQUIRE(intersection.normal.y ==
            Catch::Detail::Approx(normal.y).epsilon(0.01));
    REQUIRE(intersection.normal.z == Catch::Detail::Approx(normal.z));
  }

  SECTION("should intersect correctly with lens with negative radius") {
    auto testData = GENERATE(table<owl::vec3f, owl::vec3f>(
        {{{0, 0, -1}, {0, 0, 2}},
         {normalize(owl::vec3f(0, 1, -1)), {0, 0.98648f, 2.01352f}}}));
    owl::vec3f direction = std::get<0>(testData);
    owl::vec3f position = std::get<1>(testData);

    Lens lens(-35.98738, 1.21638, 1.54, 23.716, 2);

    Intersection intersection = lens.intersect({0, 0, 3}, direction);

    REQUIRE(intersection.position.x == Catch::Detail::Approx(position.x));
    REQUIRE(intersection.position.y == Catch::Detail::Approx(position.y));
    REQUIRE(intersection.position.z == Catch::Detail::Approx(position.z));
  }
}

TEST_CASE("LensSystem::()") {
  SECTION("should calculate lens centers correctly") {
    LensSystem lensSystem("test", {{{40.93, 10.64, 1, 17.3},
                                    {183.92, 7.05, 1.6910, 16.5},
                                    {-48.91, 79.831, 1, 16.5}}});

    REQUIRE(lensSystem.lenses[0].center == Catch::Detail::Approx(97.521));
    REQUIRE(lensSystem.lenses[1].center == Catch::Detail::Approx(86.8810043));
    REQUIRE(lensSystem.lenses[2].center == Catch::Detail::Approx(79.8310013f));
  }
}

TEST_CASE("LensSystem::createIdealInteractionSequence") {
  SECTION("should create an ideal interaction sequence") {
    LensSystem lensSystem("test", {{{40.93, 10.64, 1, 17.3},
                                    {183.92, 7.05, 1.6910, 16.5},
                                    {-48.91, 79.831, 1, 16.5}}});

    auto sequence = lensSystem.createIdealInteractionSequence();

    REQUIRE(sequence ==
            std::vector<InteractionEvent>({{0, true}, {1, true}, {2, true}}));
  }
}

TEST_CASE("LensSystem::traceToFilmPlane") {
  SECTION("should trace ray along optical axis to origin") {
    LensSystem lensSystem = getAvailableLensSystems()[3];
    auto sequence = lensSystem.createIdealInteractionSequence();

    auto positionOnFilm =
        lensSystem.traceToFilmPlane(sequence, {0, 0, 190}, {0, 0, -1});

    REQUIRE(positionOnFilm == owl::vec3f(0, 0, 0));
  }
}