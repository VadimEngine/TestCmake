#include "MenuPage.h"


MenuPage::MenuPage() {

}

MenuPage::~MenuPage() {

}

void MenuPage::buildImGui() {
    ImGui::Begin("ImGui Window");
    ImGui::Text("Hello, ImGui!");
    ImGui::End();
}