#ifndef RR_LENSFLARES_SRC_LENSSYSTEM_H_
#define RR_LENSFLARES_SRC_LENSSYSTEM_H_

#include "owl/common/math/vec.h"
#include "owl/owl.h"
#include <string>
#include <vector>

struct Intersection {
  owl::vec3f position;
};

struct Lens {
  float curvatureRadius;
  float thickness;
  float ior;
  float apertureRadius;
  Lens(float curvatureRadius, float thickness, float ior, float apertureRadius);

  Intersection intersect(const owl::vec3f &position, const owl::vec3f &direction);
};

struct IntersectionSequence{
  std::vector<int> interfaceIndices;
};

struct LensSystem {
  std::string name;
  std::vector<Lens> lenses;
  LensSystem(const std::string &name, const std::vector<Lens> &lenses);
  Intersection traceRay(const owl::vec3f &position, const owl::vec3f &direction);
};

#endif // RR_LENSFLARES_SRC_LENSSYSTEM_H_
