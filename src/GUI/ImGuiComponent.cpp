#include "ImGuiComponent.h"

ImGuiComponent::ImGuiComponent() {}

ImGuiComponent::~ImGuiComponent() {}

void ImGuiComponent::initializeImGui(GLFWwindow* window) {
    const char* glsl_version = "#version 330";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //disable .ini file generations
    io.IniFilename = nullptr;

    // Setup Platform/Renderer backends
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        std::cout << "ImGui_ImplGlfw_InitForOpenGL failed" << std::endl;
        throw std::runtime_error("ImGui_ImplGlfw_InitForOpenGL error");
    }

    if (!ImGui_ImplOpenGL3_Init(glsl_version)) {
        std::cout << "ImGui_ImplOpenGL3_Init failed" << std::endl;
        throw std::runtime_error("ImGui_ImplOpenGL3_Init error");
    }
}

void ImGuiComponent::deinitialize() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiComponent::render() {
    startRender();
    buildImGui();
    endRender();
}

void ImGuiComponent::startRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiComponent::buildImGui() {}

void ImGuiComponent::endRender() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiComponent::setRemove(const bool remove) {
    mIsRemove_ = remove;
}

bool ImGuiComponent::isRemove() const {
    return mIsRemove_;
}