#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_RESOURCES_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_RESOURCES_H_

#include <filesystem>

class Resources {
public:
  static std::filesystem::path getShaderResourceByName(const std::string &name);
  static std::filesystem::path getMeshResourceByName(const std::string &name);

private:
  static std::filesystem::path getResource(const std::string &category, const std::string &name);
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_RESOURCES_H_
