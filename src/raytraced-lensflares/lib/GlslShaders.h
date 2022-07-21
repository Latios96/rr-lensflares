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
  static GLuint loadGeometryShader();
  static GLuint loadFragmentShader();
  static GLuint createProgramm();

private:
  static std::string loadShaderFile(const std::string &filename);
  static GLuint compileShader(const char *shaderCode, GLenum shaderType);
  static void checkLinkError(GLuint program);
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_LIB_GLSLSHADERS_H_
