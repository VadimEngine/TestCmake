#include "App.h"
#include "RPG2DSceneGUI.h"
#include "RPG2DScene.h"

namespace rpg_2d {

    RPG2DSceneGUI::RPG2DSceneGUI(RPG2DScene& theScene)
        : mScene_(theScene) {
        mVSyncEnabled_ = mScene_.getApp().getWindow().getGLFWSwapInterval();
        mVolume_ = mScene_.getApp().getAudioManger().getGain();
    }

    RPG2DSceneGUI::~RPG2DSceneGUI() {}

    void RPG2DSceneGUI::buildImGui() {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
        ImGui::Begin("Settings");
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 0.40f));
        if (ImGui::Button("Back")) {
            mScene_.getApp().setScene(new GamesScene(mScene_.getApp()));
            mScene_.setRemove(true);
        }
        ImGui::PopStyleColor();
        ImGui::Text("2D RPG Scene");
        ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
        if (ImGui::Checkbox("vSync", &mVSyncEnabled_)) {
            mScene_.getApp().getWindow().setVSync(mVSyncEnabled_);
        }
        if (ImGui::SliderFloat("Volume", &mVolume_, 0.f, 1.f)) {
            mScene_.getApp().getAudioManger().setGain(mVolume_);
        }

        ImGui::End();
    }

} // namespace rpg_2d