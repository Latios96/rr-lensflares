#ifndef RR_LENSFLARES_SRC_LENSSYSTEM_H_
#define RR_LENSFLARES_SRC_LENSSYSTEM_H_

#include "Ray.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <ostream>
#include <string>
#include <vector>

struct Intersection {
  glm::vec3 position;
  glm::vec3 normal;

  static Intersection createInvalid() {
    return {{std::numeric_limits<float>::min(), std::numeric_limits<float>::min(),
             std::numeric_limits<float>::min()},
            {std::numeric_limits<float>::min(), std::numeric_limits<float>::min(),
             std::numeric_limits<float>::min()}};
  }

  bool isValid() { return position != glm::vec3(std::numeric_limits<float>::min()); }

  glm::vec3 reflect(const glm::vec3 &direction) const {
    return direction - 2.0f * glm::dot(direction, normal) * normal;
  }

  glm::vec3 refract(const glm::vec3 &direction, float iorIn, float iorOut) const {
    float cosi = std::clamp(glm::dot(direction, normal), -1.0f, 1.0f);
    glm::vec3 n = normal;
    if (cosi < 0) {
      cosi = -cosi;
    } else {
      std::swap(iorIn, iorOut);
      n = -normal;
    }
    float eta = iorIn / iorOut;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? direction : eta * direction + (eta * cosi - sqrtf(k)) * n;
  }
};

struct LensData {
  float curvatureRadius;
  float thickness;
  float ior;
  float apertureRadius;
  LensData(float curvatureRadius, float thickness, float ior, float apertureRadius);
};

struct Lens : public LensData {
  float center;
  Lens(float curvatureRadius, float thickness, float ior, float apertureRadius, float center);
  Intersection intersect(const glm::vec3 &position, const glm::vec3 &direction) const;
};

struct InteractionEvent {
  int lensIndex;
  bool refract;
  InteractionEvent(int lensIndex, bool refract);
  bool operator==(const InteractionEvent &rhs) const;
  bool operator!=(const InteractionEvent &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, const InteractionEvent &event);
};

struct ReflectionEvent {
  int indexFirstReflected, indexLastReflected;
  ReflectionEvent(int indexFirstReflected, int indexLastReflected);
  bool operator==(const ReflectionEvent &rhs) const;
  bool operator!=(const ReflectionEvent &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, const ReflectionEvent &event);
};

struct LensSystem {
  std::string name;
  std::vector<Lens> lenses;
  float focalLength;
  LensSystem(const std::string &name, float focalLength, const std::vector<LensData> &lensesData);
  Intersection traceRay(const glm::vec3 &position, const glm::vec3 &direction);

  std::vector<InteractionEvent> createIdealInteractionSequence() const;
  std::vector<ReflectionEvent> createReflectionSequences() const;

  glm::vec3 traceToFilmPlane(const std::vector<InteractionEvent> &events, const glm::vec3 &position,
                             const glm::vec3 &direction) const;

  Ray traceRayFromPlaneToWorld(const Ray &ray) const;

  float focusPointDistance();
  float getFov(const float filmbackSize) const;
};

#endif // RR_LENSFLARES_SRC_LENSSYSTEM_H_
