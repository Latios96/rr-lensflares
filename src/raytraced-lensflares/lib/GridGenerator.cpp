#include "GridGenerator.h"
#include <spdlog/spdlog.h>

void GridGenerator::generateGrid(Mesh &mesh, int subdivs) {
  generatePoints(mesh, subdivs);
  generateIndices(mesh, subdivs);
}

void GridGenerator::generatePoints(Mesh &mesh, int subdivs) {
  const float subdivStep = 1.0f / subdivs;
  mesh.vertices.reserve((subdivs + 1) * (subdivs + 1));
  spdlog::info("reserved {} for points", mesh.vertices.capacity());
  for (int y = 0; y <= subdivs; y++) {
    for (int x = 0; x <= subdivs; x++) {
      mesh.vertices.push_back(
          Vertex(glm::vec3(-0.5f + subdivStep * x, -0.5f + subdivStep * y, 0.0f)));
    }
  }
  spdlog::info("used {} for points", mesh.vertices.size());
}

void GridGenerator::generateIndices(Mesh &mesh, int subdivs) {
  mesh.indices.reserve(subdivs * subdivs * 3 * 2);
  spdlog::info("reserved {} for indices", mesh.indices.capacity());
  for (int row = 0; row < subdivs; row++) {
    int startIndexForRow = 0 + row * (subdivs + 1);
    for (int quad = 0; quad < subdivs; quad++) {
      int startIndexForQuad = startIndexForRow + quad;
      mesh.indices.push_back(startIndexForQuad);
      mesh.indices.push_back(startIndexForQuad + 1);
      mesh.indices.push_back(startIndexForQuad + subdivs + 1);

      mesh.indices.push_back(startIndexForQuad + 1);
      mesh.indices.push_back(startIndexForQuad + subdivs + 2);
      mesh.indices.push_back(startIndexForQuad + subdivs + 1);
    }
  }
  spdlog::info("used {} for indices", mesh.indices.size());
}
