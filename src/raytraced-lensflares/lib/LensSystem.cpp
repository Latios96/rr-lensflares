#include "LensSystem.h"

LensSystem::LensSystem(const std::string &name, const std::vector<Lens> &lenses)
    : name(name), lenses(lenses) {}

Intersection LensSystem::traceRay(const owl::vec3f &position,
                                  const owl::vec3f &direction) {
  Intersection intersection;
  for (auto &lens : lenses) {
    intersection = lens.intersect(position, direction);
  }
  return intersection;
}

Lens::Lens(float curvatureRadius, float thickness, float ior,
           float apertureRadius)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior),
      apertureRadius(apertureRadius) {}

Intersection Lens::intersect(const owl::vec3f &position,
                             const owl::vec3f &direction) {
  return Intersection();
}
