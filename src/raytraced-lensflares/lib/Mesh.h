#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_MESH_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_MESH_H_

struct Vertex {
  glm::vec3 pos;
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
};

#include <glm/vec3.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_MESH_H_
