#include "LensSystem.h"

LensSystem::LensSystem(const std::string &name, const std::vector<Lens> &lenses)
    : name(name), lenses(lenses) {}
Lens::Lens(float curvatureRadius, float thickness, float ior,
           float apertureRadius)
    : curvatureRadius(curvatureRadius), thickness(thickness), ior(ior),
      apertureRadius(apertureRadius) {}
