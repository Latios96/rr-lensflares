#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <fmt/format.h>
#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <vector>
#define TINYOBJLOADER_IMPLEMENTATION
#include "LensSystem.h"
#include "LensSystems.h"
#include "tiny_obj_loader.h"

#include <filesystem>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <whereami.h>

struct Vertex {
  glm::vec3 pos;
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
};

static void error_callback(int error, const char *description) {
  std::cerr << fmt::format("Error: {}", description) << std::endl;
}
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
  fprintf(stderr,
          "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity,
          message);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void read_obj(std::string objPath, Mesh &mesh) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string err;

  bool success =
      tinyobj::LoadObj(&attrib, &shapes, &materials, &err, objPath.data());
  if (!success) {
    std::cout << "Error when reading obj file: " + err << std::endl;
    return;
  }

  for (int i = 0; i < attrib.vertices.size(); i = i + 3) {
    mesh.vertices.push_back(
        {{attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2]}});
  }
  for (auto &shape : shapes) {
    for (auto &indice : shape.mesh.indices) {
      mesh.indices.push_back(indice.vertex_index);
    }
  }
}

GLuint compile_shader(const char *shaderCode, GLenum shaderType) {
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

    std::cerr << fmt::format(
        "Error when compiling {} shader: :\n{}",
        shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment", infoLog);
    throw std::runtime_error("Error when compiling shader");
  }

  return shader;
}

static std::string loadShaderFile(const std::string &filename) {
  int length = wai_getExecutablePath(NULL, 0, NULL);
  std::string executablePathStr;
  executablePathStr.resize(length);
  wai_getExecutablePath(executablePathStr.data(), length, NULL);
  auto executablePath = std::filesystem::path(executablePathStr);
  auto executableDirectory = executablePath.parent_path();
  const std::filesystem::path filePath =
      executableDirectory / "shader" / filename;
  if (!std::filesystem::exists(filePath)) {
    std::string message =
        fmt::format("Shader source file at given path {} does not exist.",
                    filePath.string());
    spdlog::error(message);
    throw std::runtime_error(message);
  }
  std::ifstream t(filePath);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

static GLuint loadVertexShader() {
  static std::string vertexShaderCode = loadShaderFile("vertex.glsl");
  return compile_shader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
}

static GLuint loadFragmentShader() {
  static std::string vertexShaderCode = loadShaderFile("fragment.glsl");
  return compile_shader(vertexShaderCode.c_str(), GL_FRAGMENT_SHADER);
}

int main() {
  auto console = spdlog::stdout_color_mt("console");
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(640, 480, "OpenGL Teapot", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  gladLoadGL();
  glfwSwapInterval(1);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, nullptr);

  Mesh mesh;
  read_obj("C:\\workspace\\opengl-starter\\teapot.obj", mesh);

  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex),
               mesh.vertices.data(), GL_STATIC_DRAW);

  GLuint indices_buffer;
  glGenBuffers(1, &indices_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(),
               GL_STATIC_DRAW);

  const GLuint vertex_shader = loadVertexShader();
  const GLuint fragment_shader = loadFragmentShader();

  const GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  const GLint mvp_location = glGetUniformLocation(program, "MVP");
  const GLint vpos_location = glGetAttribLocation(program, "vPos");

  GLuint vertex_array;
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, pos));

  LensSystem lensSystem = getAvailableLensSystems()[1];
  auto sequences = lensSystem.createReflectionSequences();
  GLuint ssbo;
  glGenBuffers(1, &ssbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  glBufferData(GL_SHADER_STORAGE_BUFFER, sequences.size() * sizeof(int) * 2,
               sequences.data(),
               GL_STATIC_DRAW); // sizeof(data) only works for statically sized
                                // C/C++ arrays.
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    const float ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4x4 m(1.0);
    glm::mat4x4 p(1.0);
    glm::mat4x4 mvp(1.0);
    p = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mvp = p * m;

    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)&mvp);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}

//! [code]
