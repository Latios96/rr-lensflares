#include "GlslShaders.h"
#include "Resources.h"

GLuint GlslShaders::loadVertexShader() {
  static std::string vertexShaderCode = loadShaderFile("vertex.glsl");
  return compileShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
}

GLuint GlslShaders::loadFragmentShader() {
  static std::string vertexShaderCode = loadShaderFile("fragment.glsl");
  return compileShader(vertexShaderCode.c_str(), GL_FRAGMENT_SHADER);
}

std::string GlslShaders::loadShaderFile(const std::string &filename) {
  std::filesystem::path executableDirectory = Utils::getExecutableDirectory();

  const std::filesystem::path filePath = Resources::getShaderResourceByName(filename);

  if (!std::filesystem::exists(filePath)) {
    Utils::logAndThrow<std::runtime_error>(
        fmt::format("Shader source file at given path {} does not exist.", filePath.string()));
  }

  std::ifstream t(filePath);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

GLuint GlslShaders::compileShader(const char *shaderCode, GLenum shaderType) {
  const GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderCode, nullptr);
  glCompileShader(shader);

  GLint isCompiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    std::string infoLog;
    infoLog.resize(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(shader);

    Utils::logAndThrow<std::runtime_error>(
        fmt::format("Error when compiling {} shader: :\n{}",
                    shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment", infoLog));
  }

  return shader;
}
