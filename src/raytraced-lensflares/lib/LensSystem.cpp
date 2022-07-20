#include "LensSystem.h"
#include <fmt/format.h>

LensSystem::LensSystem(const std::string &name, float focalLength,
                       const std::vector<LensData> &lensesData)
    : name(name), focalLength(focalLength) {
  float center = 0;
  for (int i = lensesData.size() - 1; i >= 0; i--) {
    center += lensesData[i].thickness;
    Lens lens(lensesData[i].curvatureRadius, lensesData[i].thickness, lensesData[i].ior,
              lensesData[i].apertureRadius, center);
    lenses.insert(lenses.begin(), lens);
  }
}

Intersection LensSystem::traceRay(const glm::vec3 &position, const glm::vec3 &direction) {
  Intersection intersection;
  for (auto &lens : lenses) {
    intersection = lens.intersect(position, direction);
  }
  return intersection;
}

std::vector<InteractionEvent> LensSystem::createIdealInteractionSequence() const {
  std::vector<InteractionEvent> events;
  for (int i = 0; i < lenses.size(); i++) {
    events.emplace_back(i, true);
  }
  return events;
}

std::vector<ReflectionEvent> LensSystem::createReflectionSequences() const {
  const int totalSequenceCount = lenses.size() * (lenses.size() - 2) / 2;
  std::vector<ReflectionEvent> sequences;
  sequences.reserve(totalSequenceCount);
  for (int firstIndex = 0; firstIndex < lenses.size(); firstIndex++) {
    for (int lastIndex = lenses.size() - 1; lastIndex > firstIndex; lastIndex--) {
      const bool involvesAperture =
          lenses[firstIndex].curvatureRadius == 0 || lenses[lastIndex].curvatureRadius == 0;
      if (involvesAperture) {
        continue;
      }
      sequences.emplace_back(lastIndex, firstIndex);
    }
  }
  return sequences;
}

glm::vec3 LensSystem::traceToFilmPlane(const std::vector<InteractionEvent> &events,
                                       const glm::vec3 &position,
                                       const glm::vec3 &direction) const {
  glm::vec3 tracedPosition = position;
  glm::vec3 tracedDirection = direction;
  float ior = 1;
  for (auto &event : events) {
    const auto lens = lenses[event.lensIndex];
    if (lens.ior == 0) {
      continue;
    }
    const auto intersection = lens.intersect(tracedPosition, tracedDirection);
    tracedPosition = intersection.position;
    if (event.refract) {
      tracedDirection = intersection.refract(tracedDirection, ior, lens.ior);
      ior = lens.ior;
    } else {
      tracedDirection = intersection.reflect(tracedDirection);
    }
  }
  float t = (-tracedPosition.z) / tracedDirection.z;
  return tracedPosition + tracedDirection * t;
}

float LensSystem::focusPointDistance() {
  const float filmbackSize = 36;
  const float fov = getFov(filmbackSize);
  return std::atan(fov) * (filmbackSize / 2.0f);
}

float LensSystem::getFov(const float filmbackSize) const {
  return 2 * atan(filmbackSize / 2.0f * 1.0f / focalLength);
}

LensData::LensData(float curvatureRadius, float thickness, float ior, float apertureRadius)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior),
      apertureRadius(apertureRadius) {}

Intersection Lens::intersect(const glm::vec3 &position, const glm::vec3 &direction) const {
  glm::vec3 D = position - glm::vec3(0, 0, center - curvatureRadius);
  float B = dot(D, direction);
  float C = dot(D, D) - curvatureRadius * curvatureRadius;
  float B2_C = B * B - C;
  if (B2_C < 0) {
    return Intersection::createInvalid();
  }
  float sgn = (curvatureRadius * direction.z) > 0 ? 1 : -1;
  float t = sqrt(B2_C) * sgn - B;
  glm::vec3 intersectionPosition = direction * t + position;
  return {intersectionPosition,
          normalize(intersectionPosition - glm::vec3(0, 0, center - curvatureRadius))};
}

Lens::Lens(float curvatureRadius, float thickness, float ior, float apertureRadius, float center)
    : LensData(curvatureRadius, thickness, ior, apertureRadius), center(center) {}

bool InteractionEvent::operator==(const InteractionEvent &rhs) const {
  return lensIndex == rhs.lensIndex && refract == rhs.refract;
}

bool InteractionEvent::operator!=(const InteractionEvent &rhs) const { return !(rhs == *this); }

InteractionEvent::InteractionEvent(int lensIndex, bool refract)
    : lensIndex(lensIndex), refract(refract) {}

std::ostream &operator<<(std::ostream &os, const InteractionEvent &event) {
  os << "lensIndex: " << event.lensIndex << " refract: " << event.refract;
  return os;
}

ReflectionEvent::ReflectionEvent(int indexFirstReflected, int indexLastReflected)
    : indexFirstReflected(indexFirstReflected), indexLastReflected(indexLastReflected) {}

std::ostream &operator<<(std::ostream &os, const ReflectionEvent &event) {
  os << fmt::format("({},{})", event.indexFirstReflected, event.indexLastReflected);
  return os;
}

bool ReflectionEvent::operator==(const ReflectionEvent &rhs) const {
  return indexFirstReflected == rhs.indexFirstReflected &&
         indexLastReflected == rhs.indexLastReflected;
}

bool ReflectionEvent::operator!=(const ReflectionEvent &rhs) const { return !(rhs == *this); }
