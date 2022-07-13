#include "Resources.h"
#include "Utils.h"

std::filesystem::path Resources::getShaderResourceByName(const std::string &name) {
  return getResource("shader", name);
}

std::filesystem::path Resources::getMeshResourceByName(const std::string &name) {
  return getResource("meshes", name);
}

std::filesystem::path Resources::getResource(const std::string &category, const std::string &name) {
  return Utils::getExecutableDirectory() / category / name;
}
