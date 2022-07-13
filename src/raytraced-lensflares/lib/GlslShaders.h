#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GLSLSHADERS_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GLSLSHADERS_H_

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include "Utils.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sstream>
#include <whereami.h>

class GlslShaders {
public:
  static GLuint loadVertexShader();
  static GLuint loadFragmentShader();

private:
  static std::string loadShaderFile(const std::string &filename);
  static std::filesystem::path getExecutableDirectory();
  static GLuint compileShader(const char *shaderCode, GLenum shaderType);
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GLSLSHADERS_H_
