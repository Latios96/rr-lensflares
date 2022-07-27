#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_RAY_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_RAY_H_

#include <glm/vec3.hpp>

struct Ray {
  Ray();
  Ray(const glm::vec3 &position, const glm::vec3 &direction);
  Ray(const Ray &ray);
  glm::vec3 position;
  glm::vec3 direction;

  glm::vec3 toPoint(const float t) const;
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_RAY_H_
