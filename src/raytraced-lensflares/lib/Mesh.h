#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_MESH_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_MESH_H_

#include <glm/vec3.hpp>
#include <vector>

struct Vertex {
  Vertex(const glm::vec3 &pos) : pos(pos) {}

  glm::vec3 pos;
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_MESH_H_
