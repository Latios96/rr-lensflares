#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <fmt/format.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
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
#include "Mesh.h"
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
GLuint updateSSBO(GLuint ssbo, int ssboBindingLocation, const std::vector<T> &source) {
  std::vector<A> aligned;
  toAlignedVector(source, aligned);

  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  glBufferData(GL_SHADER_STORAGE_BUFFER, aligned.size() * sizeof(A), aligned.data(),
               GL_STATIC_DRAW);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ssboBindingLocation, ssbo);

  return ssbo;
}

template <typename T>
GLuint updateSSBO(GLuint ssbo, int ssboBindingLocation, const std::vector<T> &source) {
  std::vector<T> aligned;
  toAlignedVector(source, aligned);

  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  glBufferData(GL_SHADER_STORAGE_BUFFER, aligned.size() * sizeof(T), aligned.data(),
               GL_STATIC_DRAW);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ssboBindingLocation, ssbo);

  return ssbo;
}

template <typename T, typename A>
GLuint populateSSBO(int ssboBindingLocation, const std::vector<T> &source) {
  GLuint ssbo;
  glGenBuffers(1, &ssbo);
  updateSSBO<T, A>(ssbo, ssboBindingLocation, source);

  return ssbo;
}

template <typename T> GLuint populateSSBO(int ssboBindingLocation, const std::vector<T> &source) {
  return populateSSBO<T, T>(ssboBindingLocation, source);
}

static UiState uiState;

template <> struct fmt::formatter<glm::vec3> {
  template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext> auto format(glm::vec3 const &vec, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "({},{},{})", vec.x, vec.y, vec.z);
  };
};

template <> struct fmt::formatter<glm::vec2> {
  template <typename ParseContext> constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext> auto format(glm::vec2 const &vec, FormatContext &ctx) {
    return fmt::format_to(ctx.out(), "({},{})", vec.x, vec.y);
  };
};

static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {
  if (!uiState.isMovingLight) {
    return;
  }
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glm::vec2 relativePosition = glm::vec2(xpos / width, ypos / height);
  glm::vec3 positionOnFilm =
      glm::vec3(36.0f / 2 - 36 * relativePosition.x, 24.0f / 2 - 24 * relativePosition.y, 0);
  uiState.lightPositionOnFilm = positionOnFilm;
}

static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
  const bool lightMoveStart = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS;
  const bool lightMoveEnd = button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE;

  if (lightMoveStart) {
    uiState.isMovingLight = true;
  } else if (lightMoveEnd) {
    uiState.isMovingLight = false;
  }
}

static glm::ivec2 getInitialLightPositionOnScreen(GLFWwindow *window) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  return {width / 2, height / 2};
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
  glfwSetCursorPosCallback(window, cursorPositionCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);

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

  const GLuint program = GlslShaders::createProgramm();

  const GLint mvp_location = glGetUniformLocation(program, "MVP");
  const GLint lightDirectionPosition = glGetUniformLocation(program, "lightDirection");
  const GLint sequenceIndexLocation = glGetUniformLocation(program, "sequenceIndex");
  const GLint vpos_location = glGetAttribLocation(program, "vPos");

  GLuint vertex_array;
  glGenVertexArrays(1, &vertex_array);
  glBindVertexArray(vertex_array);
  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, pos));

  uiState.lightPositionOnFilm = glm::vec3(0, 0, 0);
  static UiState previousState = uiState;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  auto availableLensSystems = getAvailableLensSystems();

  LensSystem lensSystem = availableLensSystems[uiState.currentLensIndex];
  auto sequences = lensSystem.createReflectionSequences();

  GLuint ssboReflectionEvents = populateSSBO<ReflectionEvent>(3, sequences);
  GLuint ssboLensSystem = populateSSBO<Lens>(4, lensSystem.lenses);

  while (!glfwWindowShouldClose(window)) {
    if (uiState.currentLensIndex != previousState.currentLensIndex) {
      lensSystem = availableLensSystems[uiState.currentLensIndex];
      sequences = lensSystem.createReflectionSequences();

      updateSSBO<ReflectionEvent>(ssboReflectionEvents, 3, sequences);
      updateSSBO<Lens>(ssboLensSystem, 4, lensSystem.lenses);
    }
    previousState = uiState;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4x4 m(1.0);
    glm::mat4x4 p(1.0);
    glm::mat4x4 mvp(1.0);

    const glm::mat4x4 view = glm::lookAt(glm::vec3(0, 0, -lensSystem.focusPointDistance()),
                                         glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    p = glm::perspective(lensSystem.getFov(36), aspectRatio, 0.0f, 500.0f) * view;
    mvp = p * m;

    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)&mvp);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboReflectionEvents);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboLensSystem);

    glm::vec3 lightDirection = glm::normalize(uiState.lightPositionOnFilm -
                                              glm::vec3(0, 0, -lensSystem.focusPointDistance()));
    glUniform3fv(lightDirectionPosition, 1, &lightDirection[0]);

    for (int i = 0; i < sequences.size(); i++) {
      glUniform1i(sequenceIndexLocation, i);
      glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
    }

    renderUiControls(uiState, availableLensSystems, sequences);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}

//! [code]
