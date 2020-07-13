#include "imgu_manager.h"

imgu_manager::imgu_manager(GLFWwindow* Window) : window(Window)
{
    const char* glsl_version = "#version 130";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    show_demo_window = true;
    show_another_window = false;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

imgu_manager::~imgu_manager() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void imgu_manager::Init() {

}

void imgu_manager::Begin() {
    glDisable(GL_STENCIL_TEST);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void imgu_manager::End() {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glEnable(GL_STENCIL_TEST);
}

void imgu_manager::drowPostProcessing(PostProcessing &data) {
    ImGui::Begin("Post processing");
    ImGui::BeginGroup();
    ImGui::SliderFloat("exposure", &data.exposure, 0.0f, 0.5f);
    ImGui::RadioButton("off", &data.mode, 0);
    ImGui::RadioButton("kernel", &data.mode, 1);
    ImGui::RadioButton("grayscale", &data.mode, 2);
    ImGui::RadioButton("inversion", &data.mode, 3);
    ImGui::SliderFloat("offset", &data.offset, 0.0f, 0.1f);
    ImGui::InputFloat3("1",&data.kernelMats[data.currentMat][0], 3);
    ImGui::InputFloat3("2",&data.kernelMats[data.currentMat][3], 3);
    ImGui::InputFloat3("3",&data.kernelMats[data.currentMat][6], 3);
    ImGui::Combo("Matrix", &data.currentMat, &data.kernelNames[0], data.kernelMats.size());
    ImGui::SliderFloat("gamma", &data.gamma, 1.0f, 3.0f);
    ImGui::EndGroup();
    ImGui::End();
}

