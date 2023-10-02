#include "BasicScene.h"
#include "BasicSceneGUI.h"

BasicSceneGUI::BasicSceneGUI(BasicScene* theScene)
    : mpScene_(theScene) {}

BasicSceneGUI::~BasicSceneGUI() {}

void BasicSceneGUI::buildImGui() {
    static char temp[128];

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    ImGui::Text("Basic Scene");
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
    ImGui::InputText("Input String", temp, IM_ARRAYSIZE(temp));
    ImGui::End();
};