#include "LensSystem.h"
#include "LensSystems.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Lens::intersect") {
  SECTION("should intersect correctly with lens with positive radius") {
    auto testData = GENERATE(table<glm::vec3, glm::vec3, glm::vec3>(
        {{{0, 0, -1}, {0, 0, 2}, {0, 0, 1}},
         {normalize(glm::vec3(0, 1, -1)), {0, 1.0143f, 1.9857f}, {0, 0.0281799994f, 0.9996f}}}));
    glm::vec3 direction = std::get<0>(testData);
    glm::vec3 position = std::get<1>(testData);
    glm::vec3 normal = std::get<2>(testData);

    Lens lens(35.98738, 1.21638, 1.54, 23.716, 2);

    Intersection intersection = lens.intersect({0, 0, 3}, direction);

    REQUIRE(intersection.position.x == Catch::Approx(position.x));
    REQUIRE(intersection.position.y == Catch::Approx(position.y));
    REQUIRE(intersection.position.z == Catch::Approx(position.z));

    REQUIRE(intersection.normal.x == Catch::Approx(normal.x));
    REQUIRE(intersection.normal.y == Catch::Approx(normal.y).epsilon(0.01));
    REQUIRE(intersection.normal.z == Catch::Approx(normal.z));
  }

  SECTION("should intersect correctly with lens with negative radius") {
    auto testData = GENERATE(table<glm::vec3, glm::vec3>(
        {{{0, 0, -1}, {0, 0, 2}}, {normalize(glm::vec3(0, 1, -1)), {0, 0.98648f, 2.01352f}}}));
    glm::vec3 direction = std::get<0>(testData);
    glm::vec3 position = std::get<1>(testData);

    Lens lens(-35.98738, 1.21638, 1.54, 23.716, 2);

    Intersection intersection = lens.intersect({0, 0, 3}, direction);

    REQUIRE(intersection.position.x == Catch::Approx(position.x));
    REQUIRE(intersection.position.y == Catch::Approx(position.y));
    REQUIRE(intersection.position.z == Catch::Approx(position.z));
  }
}

TEST_CASE("LensSystem::()") {
  SECTION("should calculate lens centers correctly") {
    LensSystem lensSystem(
        "test",
        {{{40.93, 10.64, 1, 17.3}, {183.92, 7.05, 1.6910, 16.5}, {-48.91, 79.831, 1, 16.5}}});

    REQUIRE(lensSystem.lenses[0].center == Catch::Approx(97.521));
    REQUIRE(lensSystem.lenses[1].center == Catch::Approx(86.8810043));
    REQUIRE(lensSystem.lenses[2].center == Catch::Approx(79.8310013f));
  }
}

TEST_CASE("LensSystem::createIdealInteractionSequence") {
  SECTION("should create an ideal interaction sequence") {
    LensSystem lensSystem(
        "test",
        {{{40.93, 10.64, 1, 17.3}, {183.92, 7.05, 1.6910, 16.5}, {-48.91, 79.831, 1, 16.5}}});

    auto sequence = lensSystem.createIdealInteractionSequence();

    REQUIRE(sequence == std::vector<InteractionEvent>({{0, true}, {1, true}, {2, true}}));
  }
}

TEST_CASE("LensSystem::traceToFilmPlane") {
  SECTION("should trace ray along optical axis to origin") {
    LensSystem lensSystem = getAvailableLensSystems()[3];
    auto sequence = lensSystem.createIdealInteractionSequence();

    auto positionOnFilm = lensSystem.traceToFilmPlane(sequence, {0, 0, 190}, {0, 0, -1});

    REQUIRE(positionOnFilm == glm::vec3(0, 0, 0));
  }
}

TEST_CASE("LensSystem::createReflectionSequences") {
  SECTION("should correctly create sequence for system with two lenses") {
    LensSystem lensSystem = getAvailableLensSystems()[0];

    auto sequence = lensSystem.createReflectionSequences();

    REQUIRE(sequence == std::vector<ReflectionEvent>({{1, 0}}));
  }
  SECTION("should correctly create sequence for system with six lenses and one "
          "aperture") {
    LensSystem lensSystem = getAvailableLensSystems()[1];

    auto sequence = lensSystem.createReflectionSequences();
    // 2 is aperture, skip it
    REQUIRE(sequence == std::vector<ReflectionEvent>({{6, 0},
                                                      {5, 0},
                                                      {4, 0},
                                                      {3, 0},
                                                      {1, 0},
                                                      {6, 1},
                                                      {5, 1},
                                                      {4, 1},
                                                      {3, 1},
                                                      {6, 3},
                                                      {5, 3},
                                                      {4, 3},
                                                      {6, 4},
                                                      {5, 4},
                                                      {6, 5}}));
  }
}