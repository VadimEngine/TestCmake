#include "App.h"
#include "PongSceneGUI.h"
#include "PongScene.h"

PongSceneGUI::PongSceneGUI(PongScene& theScene)
    : mScene_(theScene) {
    mVSyncEnabled_ =  mScene_.getApp().getWindow().getGLFWSwapInterval();
}

PongSceneGUI::~PongSceneGUI() {}

void PongSceneGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new MenuScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::Text("Pong Scene");
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
    if (ImGui::Checkbox("vSync", &mVSyncEnabled_)) {
        mScene_.getApp().getWindow().setVSync(mVSyncEnabled_);
    }
    ImGui::End();
}