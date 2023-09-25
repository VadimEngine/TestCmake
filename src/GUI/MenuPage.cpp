#include "MenuPage.h"

MenuPage::MenuPage() {}

MenuPage::~MenuPage() {}

void MenuPage::buildImGui() {
    static char temp[128];

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    ImGui::Text("Basic Scene");
    ImGui::InputText("Input String", temp, IM_ARRAYSIZE(temp));
    ImGui::End();
}