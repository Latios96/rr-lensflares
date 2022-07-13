#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GEOMETRY_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GEOMETRY_H_

#include <glm/vec3.hpp>
#include <spdlog/spdlog.h>
#include <vector>

struct Vertex {
  glm::vec3 pos;
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
};

void readObj(std::string objPath, Mesh &mesh);

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GEOMETRY_H_
