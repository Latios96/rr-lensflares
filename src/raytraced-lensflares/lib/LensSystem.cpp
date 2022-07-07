#include "LensSystem.h"
#include "owl/common/math/vec.h"

LensSystem::LensSystem(const std::string &name,
                       const std::vector<LensData> &lensesData)
    : name(name) {
  float center = 0;
  for (int i = lensesData.size() - 1; i >= 0; i--) {
    center += lensesData[i].thickness;
    Lens lens(lensesData[i].curvatureRadius, lensesData[i].thickness,
              lensesData[i].ior, lensesData[i].apertureRadius, center);
    lenses.insert(lenses.begin(), lens);
    center += lensesData[i].thickness;
  }
}

Intersection LensSystem::traceRay(const owl::vec3f &position,
                                  const owl::vec3f &direction) {
  Intersection intersection;
  for (auto &lens : lenses) {
    intersection = lens.intersect(position, direction);
  }
  return intersection;
}
std::vector<InteractionEvent>
LensSystem::createIdealInteractionSequence() const {
  std::vector<InteractionEvent> events;
  for (int i = 0; i < lenses.size(); i++) {
    events.emplace_back(i, true);
  }
  return events;
}

LensData::LensData(float curvatureRadius, float thickness, float ior,
                   float apertureRadius)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior),
      apertureRadius(apertureRadius) {}

Intersection Lens::intersect(const owl::vec3f &position,
                             const owl::vec3f &direction) const {
  owl::vec3f D = position - owl::vec3f(0, 0, center - curvatureRadius);
  float B = dot(D, direction);
  float C = dot(D, D) - curvatureRadius * curvatureRadius;
  float B2_C = B * B - C;
  if (B2_C < 0) {
    return Intersection::createInvalid();
  }
  float sgn = (curvatureRadius * direction.z) > 0 ? 1 : -1;
  float t = sqrt(B2_C) * sgn - B;
  owl::vec3f intersectionPosition = direction * t + position;
  return {intersectionPosition,
          normalize(intersectionPosition -
                    owl::vec3f(0, 0, center - curvatureRadius))};
}
Lens::Lens(float curvatureRadius, float thickness, float ior,
           float apertureRadius, float center)
    : LensData(curvatureRadius, thickness, ior, apertureRadius),
      center(center) {}

bool InteractionEvent::operator==(const InteractionEvent &rhs) const {
  return lensIndex == rhs.lensIndex && refract == rhs.refract;
}
bool InteractionEvent::operator!=(const InteractionEvent &rhs) const {
  return !(rhs == *this);
}
InteractionEvent::InteractionEvent(int lensIndex, bool refract)
    : lensIndex(lensIndex), refract(refract) {}
std::ostream &operator<<(std::ostream &os, const InteractionEvent &event) {
  os << "lensIndex: " << event.lensIndex << " refract: " << event.refract;
  return os;
}
