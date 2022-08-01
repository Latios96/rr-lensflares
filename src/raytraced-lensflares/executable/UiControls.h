#ifndef RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_EXECUTABLE_UICNTROLS_H_
#define RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_EXECUTABLE_UICNTROLS_H_

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

struct UiState {
  int currentLensIndex = 0;
  bool isMovingLight;
  glm::vec3 lightPosition;
  int subdivs = 30;
  bool lockLight = false;
  bool useBladedTexture = true;
  float intensityCutoff = 0.03f;
  float lightIntensity = 1;
};

void renderUiControls(UiState &uiState, const std::vector<LensSystem> &availableLensSystems,
                      const std::vector<ReflectionEvent> &sequences) {
  // Poll and handle events (inputs, window resize, etc.)
  // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants
  // to use your inputs.
  // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application,
  // or clear/overwrite your copy of the mouse data.
  // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main
  // application, or clear/overwrite your copy of the keyboard data. Generally you may always pass
  // all inputs to dear imgui, and hide them from your application based on those two flags.
  glfwPollEvents();

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named
  // window.
  {

    ImGui::Begin("Controls"); // Create a window called "Hello, world!" and append into it.

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    const int rayCount = sequences.size() * (uiState.subdivs + 1) * (uiState.subdivs + 1);
    ImGui::Text(fmt::format(std::locale("en_US.UTF-8"),
                            "Tracing trough {} lenses ({} reflection sequences, {:L} rays)",
                            availableLensSystems[uiState.currentLensIndex].lenses.size(),
                            sequences.size(), rayCount)
                    .c_str());

    const char *combo_preview_value = availableLensSystems[uiState.currentLensIndex].name.c_str();
    if (ImGui::BeginCombo("Lenses", combo_preview_value)) {
      for (int n = 0; n < availableLensSystems.size(); n++) {
        const bool is_selected = (uiState.currentLensIndex == n);
        if (ImGui::Selectable(availableLensSystems[n].name.c_str(), is_selected))
          uiState.currentLensIndex = n;

        if (is_selected)
          ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }

    ImGui::Checkbox("Lock light position", &uiState.lockLight);
    ImGui::Checkbox("Use bladed aperture texture", &uiState.useBladedTexture);
    ImGui::SliderInt("Subdivisions", &uiState.subdivs, 0, 300);
    ImGui::SliderFloat("Intensity cutoff", &uiState.intensityCutoff, 0, 0.1);
    ImGui::SliderFloat("Light Intensity", &uiState.lightIntensity, 1, 50);

    ImGui::End();
  }

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};

#endif // RR_LENSFLARES_SRC_RAYTRACED_LENSFLARES_EXECUTABLE_UICNTROLS_H_
