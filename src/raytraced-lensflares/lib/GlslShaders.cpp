#include "GlslShaders.h"
#include "Resources.h"

GLuint GlslShaders::loadVertexShader() {
  static std::string vertexShaderCode = loadShaderFile("vertex.glsl");
  return compileShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
}

GLuint GlslShaders::loadGeometryShader() {
  static std::string geometryShaderCode = loadShaderFile("geometry.glsl");
  return compileShader(geometryShaderCode.c_str(), GL_GEOMETRY_SHADER);
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

    std::unordered_map<GLenum, std::string> shaderTypeMapping;
    shaderTypeMapping[GL_VERTEX_SHADER] = "vertex";
    shaderTypeMapping[GL_GEOMETRY_SHADER] = "geometry";
    shaderTypeMapping[GL_FRAGMENT_SHADER] = "fragment";

    Utils::logAndThrow<std::runtime_error>(fmt::format("Error when compiling {} shader: :\n{}",
                                                       shaderTypeMapping[shaderType], infoLog));
  }

  return shader;
}

GLuint GlslShaders::createProgramm() {
  const GLuint vertex_shader = GlslShaders::loadVertexShader();
  const GLuint geometry_shader = GlslShaders::loadGeometryShader();
  const GLuint fragment_shader = GlslShaders::loadFragmentShader();

  const GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, geometry_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  checkLinkError(program);

  return program;
}

void GlslShaders::checkLinkError(GLuint program) {
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    // The program is useless now. So delete it.
    glDeleteProgram(program);

    Utils::logAndThrow<std::runtime_error>(
        fmt::format("Error when linking programm: :\n{}", infoLog.data()));
  }
}
