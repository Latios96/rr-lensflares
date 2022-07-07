#include "LensSystem.h"
#include "owl/common/math/vec.h"

LensSystem::LensSystem(const std::string &name,
                       const std::vector<LensData> &lensesData)
    : name(name) {
  float center = 0;
  for (int i = lensesData.size() - 1; i >= 0; i--) {
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

LensData::LensData(float curvatureRadius, float thickness, float ior,
                   float apertureRadius)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior),
      apertureRadius(apertureRadius) {}

Intersection Lens::intersect(const owl::vec3f &position,
                             const owl::vec3f &direction) {
  return Intersection();
}
Lens::Lens(float curvatureRadius, float thickness, float ior,
           float apertureRadius, float center)
    : LensData(curvatureRadius, thickness, ior, apertureRadius),
      center(center) {}
