#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <fmt/format.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/mat4x4.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Geometry.h"
#include "GlslShaders.h"
#include "LensSystem.h"
#include "LensSystems.h"
#include "Resources.h"
#include "UiControls.h"

static void errorCallback(int error, const char *description) {
  std::cerr << fmt::format("Error: {}", description) << std::endl;
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar *message, const void *userParam) {
  fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

template <typename A, typename B>
void toAlignedVector(const std::vector<A> &source, std::vector<B> &target) {
  target.reserve(source.size());
  for (const auto &a : source) {
    target.emplace_back(a);
  }
}

template <typename T, typename A>
GLuint populateSSBO(int ssboBindingLocation, const std::vector<T> &source) {
  std::vector<A> aligned;
  toAlignedVector(source, aligned);

  GLuint ssbo;
  glGenBuffers(1, &ssbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  glBufferData(GL_SHADER_STORAGE_BUFFER, aligned.size() * sizeof(A), aligned.data(),
               GL_STATIC_DRAW);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ssboBindingLocation, ssbo);

  return ssbo;
}

int main() {
  auto console = spdlog::stdout_color_mt("console");
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(640, 480, "OpenGL Teapot", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);

  glfwMakeContextCurrent(window);
  gladLoadGL();
  glfwSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, nullptr);

  Mesh mesh;
  readObj(Resources::getMeshResourceByName("grid.obj").string(), mesh);

  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(),
               GL_STATIC_DRAW);

  GLuint indices_buffer;
  glGenBuffers(1, &indices_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int),
               mesh.indices.data(), GL_STATIC_DRAW);

  const GLuint vertex_shader = GlslShaders::loadVertexShader();
  const GLuint fragment_shader = GlslShaders::loadFragmentShader();

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

  GLuint ssboReflectionEvents = populateSSBO<ReflectionEvent, ReflectionEvent>(3, sequences);
  GLuint ssboLensSystem = populateSSBO<Lens, Lens>(4, lensSystem.lenses);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboReflectionEvents);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboLensSystem);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr);

    renderUiControls();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}

//! [code]
