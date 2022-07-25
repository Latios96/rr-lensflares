#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GEOMETRY_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GEOMETRY_H_

#include "Mesh.h"
#include <glm/vec3.hpp>
#include <spdlog/spdlog.h>
#include <vector>

void readObj(std::string objPath, Mesh &mesh);

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GEOMETRY_H_
