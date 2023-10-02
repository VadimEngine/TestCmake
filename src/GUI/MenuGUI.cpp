#include "App.h"
#include "MenuGUI.h"
#include "MenuScene.h"

MenuGUI::MenuGUI(MenuScene* theScene) 
    : mpScene_(theScene) {}

MenuGUI::~MenuGUI() {}

void MenuGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Menu", NULL,  ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text("OpenGL Menu");

    if (ImGui::Button("Basic Scene")) {
        mpScene_->getApp()->setScene(new BasicScene(mpScene_->getApp()));
    }
    if (ImGui::Button("Assimp Scene")) {
        mpScene_->getApp()->setScene(new AssimpScene(mpScene_->getApp()));
    }
    if (ImGui::Button("Exit")) {
        mpScene_->getApp()->quit();
    }

    ImGui::End();
}
