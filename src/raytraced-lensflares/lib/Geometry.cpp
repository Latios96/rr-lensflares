#include "Geometry.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

void readObj(std::string objPath, Mesh &mesh) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string err;

  bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, objPath.data());
  if (!success) {
    spdlog::error("Error when reading obj file: {}", err);
    return;
  }

  for (int i = 0; i < attrib.vertices.size(); i = i + 3) {
    mesh.vertices.push_back({{attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2]}});
  }
  for (auto &shape : shapes) {
    for (auto &indice : shape.mesh.indices) {
      mesh.indices.push_back(indice.vertex_index);
    }
  }
}
