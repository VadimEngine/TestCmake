#include "App.h"
#include "MenuGUI.h"
#include "MenuScene.h"

MenuGUI::MenuGUI(MenuScene& theScene) 
    : mScene_(theScene) {}

MenuGUI::~MenuGUI() {}

void MenuGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Menu", NULL,  ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text("OpenGL Menu");

    if (ImGui::Button("Basic Scene")) {
        mScene_.getApp().setScene(new BasicScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Scene 2d")) {
        mScene_.getApp().setScene(new Scene2d(mScene_.getApp()));
        mScene_.setRemove(true);

    }
    if (ImGui::Button("Exit")) {
        mScene_.getApp().quit();
        mScene_.setRemove(true);
    }

    ImGui::End();
}
