#ifndef RR_LENSFLARES_SRC_LENSSYSTEM_H_
#define RR_LENSFLARES_SRC_LENSSYSTEM_H_

#include "owl/common/math/vec.h"
#include "owl/owl.h"
#include <ostream>
#include <string>
#include <vector>

struct Intersection {
  owl::vec3f position;
  owl::vec3f normal;
  static Intersection createInvalid() {
    return {std::numeric_limits<float>::min()};
  }
  bool isValid() {
    return position != owl::vec3f(std::numeric_limits<float>::min());
  }
};

struct LensData {
  float curvatureRadius;
  float thickness;
  float ior;
  float apertureRadius;
  LensData(float curvatureRadius, float thickness, float ior,
           float apertureRadius);
};

struct Lens : public LensData {
  float center;
  Lens(float curvatureRadius, float thickness, float ior, float apertureRadius,
       float center);
  Intersection intersect(const owl::vec3f &position,
                         const owl::vec3f &direction);
};

struct InteractionEvent {
  int lensIndex;
  bool refract;
  InteractionEvent(int lensIndex, bool refract);
  bool operator==(const InteractionEvent &rhs) const;
  bool operator!=(const InteractionEvent &rhs) const;
  friend std::ostream &operator<<(std::ostream &os,
                                  const InteractionEvent &event);
};

struct LensSystem {
  std::string name;
  std::vector<Lens> lenses;
  LensSystem(const std::string &name, const std::vector<LensData> &lensesData);
  Intersection traceRay(const owl::vec3f &position,
                        const owl::vec3f &direction);

  std::vector<InteractionEvent> createIdealInteractionSequence() const;
};

#endif // RR_LENSFLARES_SRC_LENSSYSTEM_H_
