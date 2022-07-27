#include "Ray.h"

Ray::Ray(const glm::vec3 &position, const glm::vec3 &direction)
    : position(position), direction(direction) {}

Ray::Ray() : position(glm::vec3(0, 0, 0)), direction(glm::vec3(0, 0, 0)) {}

glm::vec3 Ray::toPoint(const float t) const { return position + direction * t; }

Ray::Ray(const Ray &ray) = default;
