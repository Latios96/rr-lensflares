#ifndef RR_LENSFLARES_SRC_LENSSYSTEM_H_
#define RR_LENSFLARES_SRC_LENSSYSTEM_H_

#include "owl/common/math/vec.h"
#include "owl/owl.h"
#include <algorithm>
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
  owl::vec3f reflect(const owl::vec3f &direction) const {
    return direction - 2.0f * dot(direction, normal) * normal;
  }
  owl::vec3f refract(const owl::vec3f &direction, float iorIn,
                     float iorOut) const {
    float cosi = std::clamp(dot(direction, normal), -1.0f, 1.0f);
    owl::vec3f n = normal;
    if (cosi < 0) {
      cosi = -cosi;
    } else {
      std::swap(iorIn, iorOut);
      n = -normal;
    }
    float eta = iorIn / iorOut;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? 0 : eta * direction + (eta * cosi - sqrtf(k)) * n;
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
                         const owl::vec3f &direction) const;
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

  owl::vec3f traceToFilmPlane(const std::vector<InteractionEvent> &events,
                              const owl::vec3f &position,
                              const owl::vec3f &direction) const;
};

#endif // RR_LENSFLARES_SRC_LENSSYSTEM_H_
